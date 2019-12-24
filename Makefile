CFLAGS=-ansi -Wall -Wextra -pedantic

all: clean myfind

myfind: bin src/*.c
	$(CC) $(CFLAGS) -g -o bin/myfind src/*.c

bin:
	mkdir bin

clean:
	rm -rf bin

.PHONY: all clean
