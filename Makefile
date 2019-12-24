CFLAGS=-ansi -Wall -pedantic

INCLUDES=-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include

all: clean myfind

myfind: bin src/*.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -o bin/myfind src/*.c

bin:
	mkdir bin

clean:
	rm -rf bin

.PHONY: all clean
