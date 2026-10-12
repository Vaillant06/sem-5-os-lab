CC      ?= gcc
CFLAGS  ?= -O2 -Wall -Wextra -std=gnu11

vfs: vfs.c
	$(CC) $(CFLAGS) -o $@ $<

test: vfs
	./test.sh

clean:
	rm -f vfs *.img
