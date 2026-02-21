CC:=clang
CFLAGS:=-std=c11 -Wall -Wextra -Werror -Wpedantic -Iinc
SOURCES:=$(wildcard src/*.c)

all: WAY_HOME

WAY_HOME:
	$(CC) $(CFLAGS) $(SOURCES) -o way_home

uninstall:
	rm -f way_home

clean:

reinstall: uninstall all
