CFLAGS=-ansi -Wall -pedantic

INCLUDES=-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include

myfind: bin *.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -o bin/myfind *.c

bin:
	mkdir bin

clean:
	rm bin/*

.PHONY: clean
