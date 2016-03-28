SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst %.c, objs/%.o, $(SOURCES))
TARGET=objs/app

CC=gcc -c -g -O2 -Wall -Wextra -I=src -std=c99
LINK=gcc -o

$(TARGET): build compile link

build:
	mkdir -p objs/src/

compile: $(OBJECTS)

objs/src/%.o: src/%.c
	$(CC) -o $@ $<

link:
	$(LINK) $(TARGET) $(OBJECTS)

clean:
	rm -rf objs/

.PHONY: build compile link clean
