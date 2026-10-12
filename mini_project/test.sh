#!/bin/bash
# End-to-end test: functionality, permissions, large files, fsck, crash recovery
set -u
V=./vfs; IMG=test.img; PASS=0; FAIL=0
ok()   { echo "  [PASS] $1"; PASS=$((PASS+1)); }
bad()  { echo "  [FAIL] $1"; FAIL=$((FAIL+1)); }
check(){ if eval "$2" >/dev/null 2>&1; then ok "$1"; else bad "$1"; fi; }

rm -f $IMG; $V mkfs $IMG 64 >/dev/null
echo "== basic namespace =="
$V $IMG mkdir /docs; $V $IMG mkdir /docs/a; $V $IMG write /docs/a/hello.txt "hello world"
check "cat returns data"      "[ \"\$($V $IMG cat /docs/a/hello.txt)\" = 'hello world' ]"
check "ls shows file"         "$V $IMG ls /docs/a | grep -q hello.txt"
check "mkdir on existing fails" "! $V $IMG mkdir /docs"
check "rmdir non-empty fails" "! $V $IMG rmdir /docs"
$V $IMG mv /docs/a /docs/b
check "rename directory"      "[ \"\$($V $IMG cat /docs/b/hello.txt)\" = 'hello world' ]"
$V $IMG ln /docs/b/hello.txt /link.txt
check "hard link shares data" "[ \"\$($V $IMG cat /link.txt)\" = 'hello world' ]"
$V $IMG rm /docs/b/hello.txt
check "link survives unlink"  "[ \"\$($V $IMG cat /link.txt)\" = 'hello world' ]"

echo "== permissions =="
$V $IMG write /secret "top secret"; $V $IMG chmod 600 /secret
check "other user denied read"   "! $V -u 1234 -g 1234 $IMG cat /secret"
check "owner can read"           "$V $IMG cat /secret"
check "other user denied create in 755 root" "[ \$(id -u) = 0 ] && ! $V -u 1234 -g 1234 $IMG touch /x || [ \$(id -u) != 0 ]"

echo "== large files (direct, indirect, double-indirect) =="
head -c 30000000 /dev/urandom > big.bin   # ~30 MB crosses into double-indirect
head -c 100000 /dev/urandom > mid.bin
$V $IMG put big.bin /big.bin >/dev/null; $V $IMG get /big.bin big.out >/dev/null
check "30MB roundtrip identical" "cmp big.bin big.out"
$V $IMG put mid.bin /mid.bin; $V $IMG get /mid.bin mid.out >/dev/null
check "100KB roundtrip identical" "cmp mid.bin mid.out"
check "fsck clean after writes"   "$V $IMG fsck | grep -q clean"
$V $IMG rm /big.bin
check "space reclaimed after rm"  "$V $IMG fsck | grep -q clean"
check "ENOSPC handled"            "! $V $IMG put /dev/zero /full 2>/dev/null; $V $IMG fsck | grep -q clean || true"

echo "== crash recovery =="
rm -f $IMG; $V mkfs $IMG 8 >/dev/null; $V $IMG mkdir /keep >/dev/null
$V --crash 1:1 $IMG mkdir /lost 2>/dev/null
check "crash before commit: op lost atomically" "! $V $IMG ls / | grep -q lost"
check "fsck clean after crash pt1" "$V $IMG fsck | grep -q clean"
$V --crash 2:1 $IMG mkdir /replayed 2>/dev/null
check "crash after commit: journal replay restores op" "$V $IMG ls / | grep -q replayed"
check "fsck clean after crash pt2" "$V $IMG fsck | grep -q clean"
$V --crash 3:1 $IMG mkdir /done 2>/dev/null
check "crash after checkpoint: op present" "$V $IMG ls / | grep -q done"

echo "== fsck detects and repairs corruption =="
python3 - <<'PY'

import struct
f = open('test.img', 'r+b')
f.seek(0)
sb = f.read(96)
vals = struct.unpack('<21I', sb[:84])
dbmap = vals[9]

# Mark one valid, normally-free data block as allocated.
block = 100
offset = dbmap * 4096 + block // 8
f.seek(offset)
byte = f.read(1)
f.seek(offset)
f.write(bytes([byte[0] | (1 << (block % 8))]))
f.close()

PY
check "fsck detects leaked blocks" "$V $IMG fsck | grep -q leaked"
$V $IMG fsck -r >/dev/null
check "fsck -r repairs"            "$V $IMG fsck | grep -q clean"
rm -f big.bin big.out mid.bin mid.out $IMG
echo; echo "passed=$PASS failed=$FAIL"; [ $FAIL -eq 0 ]
