# VFS – Linux-Based Virtual File System and Storage Management Engine

A single-file C implementation (`vfs.c`, ~1000 lines) of a persistent, inode-based
file system stored in an ordinary disk-image file. Uses only POSIX calls
(`open`, `pread`, `pwrite`, `fsync`, `ftruncate`, `clock_gettime`).

## Build & run
    make                       # builds ./vfs   (run from a normal, exec-enabled directory)
    bash test.sh               # 23 end-to-end tests (incl. crash recovery)
    ./vfs mkfs disk.img 64     # create a 64 MiB image
    ./vfs disk.img mkdir /docs
    ./vfs disk.img shell       # interactive shell (caches + metrics persist in-session)

Options: `--nosync` (skip fsync for benchmarking), `-u UID -g GID` (act as another user),
`--crash P:T` (simulate power loss at journal point P in the T-th transaction).

## Commands
mkdir touch rm rmdir mv ln ls [-l] tree stat cat put get write chmod chown su cd pwd
df stats fsck [-r] bench [MiB] [files] shell help

## On-disk layout (4 KiB blocks)
| Blocks | Contents |
|---|---|
| 0 | Superblock (geometry, free counters, clean/dirty state, mount count, alloc hint) |
| 1–64 | Write-ahead journal (header + up to 62 logged blocks) |
| next | Inode bitmap, block bitmap |
| next | Inode table, 128-byte inodes (32/block) |
| rest | Data blocks |

Inode: mode+type, uid/gid, links, size, atime/mtime/ctime, 10 direct + 1 indirect + 1 double-indirect
pointers (max file ≈ 4 GiB). Directories are files of 64-byte entries (`ino`, 59-char name), with `.` and `..`.

## Design components
- **Allocation / free space:** bitmap allocators; block allocation is *next-fit* with a persistent hint and
  per-file goal (previous block + 1), which keeps files contiguous. Freed blocks are reusable immediately.
- **Caching:** 256-buffer hashed LRU block cache; separate 1024-slot hash-indexed dentry cache for directory lookups.
- **Journaling (metadata WAL, "ordered mode"):** file data is written first; all metadata changes of an
  operation (bitmaps, inodes, directory/indirect blocks, superblock) are logged, fsynced, sealed with a
  checksummed commit record, fsynced, then checkpointed to their home locations. Mount replays committed
  transactions and discards uncommitted ones, so every operation is atomic. Oversized transactions are
  split bitmaps-first so a crash can only leak blocks, never double-allocate.
- **Consistency validation:** `fsck` walks the namespace from root and checks block ownership (duplicates,
  out-of-range pointers), per-inode block counts, link counts, orphan inodes, both bitmaps, and superblock
  counters. `fsck -r` repairs them.
- **Permissions:** UNIX owner/group/other rwx checks on every path component (`su`, `-u/-g` to switch identity; uid 0 bypasses).
- **Metrics:** `stats` reports utilization, space efficiency/internal fragmentation, extents per file and
  contiguity, allocator scan cost, I/O ops/bytes/throughput, cache hit rates, directory blocks scanned,
  journal activity. `bench` measures sequential write/read MiB/s, small-file creates/s, cold/warm lookups.

## Crash-recovery demo
    ./vfs mkfs d.img 8
    ./vfs --crash 1:1 d.img mkdir /a     # power loss before commit record -> /a never appears
    ./vfs --crash 2:1 d.img mkdir /b     # loss after commit record        -> replayed at next mount
    ./vfs d.img ls /                     # shows "[mount] journal replay: N metadata block(s) restored"
    ./vfs d.img fsck

## Known limitations (good extension ideas)
Single-threaded; no symlinks; no partial truncate; no atime updates; linear directory scan (accelerated by
the dentry cache; an on-disk hash/B-tree index would be the next step); max 62 blocks per atomic txn.
