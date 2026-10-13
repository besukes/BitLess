.PHONY: clean rmt compressor 

all: compressor

CC = gcc

CFLAGS = -Wall -ggdb -Wextra -g3 -fsanitize=address,undefined -I. -Isrc/includes -Isrc/debug

LDFLAGS = -fsanitize=address,undefined -lm

SRC = src/main.c \
	  $(wildcard src/compression/*.c) \
	  $(wildcard src/data/*.c) \
	  src/decompressor/decompressor.c \
	  src/initialization/init_clean.c \
	  src/parsing/parser.c \
	  $(wildcard src/utils/*.c) \
	  src/writing/write_out.c \
	  src/debug/debug.c

HDR = src/compression/sf_compressor.h \
	  src/data/huff_tree.h \
	  src/debug/debug.h \
	  src/decompressor/decompressor.h \
	  $(wildcard src/includes/*.h) \
	  src/initialization/init_clean.h \
	  src/parsing/parser.h \
	  $(wildcard src/utils/*.h) \
	  src/writing/write_out.h



OBJ = $(SRC:%.c=build/%.o)


compressor : $(OBJ) $(HDR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm compressor

rmt:
	rm -f tests/*_zip.txt