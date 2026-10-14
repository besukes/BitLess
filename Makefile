.PHONY: clean rmt compressor 

all: compressor

CC = gcc

CFLAGS = -Wall -ggdb -Wextra -g3 -fsanitize=address,undefined -I. -Isrc/includes -Isrc/debug

LDFLAGS = -fsanitize=address,undefined -lm

SRC = $(wildcard src/compression/*.c) \
	  $(wildcard src/algorithms/*.c) \
	  src/initialization/init_clean.c \
	  src/parsing/parser.c \
	  $(wildcard src/utils/*.c) \
	  src/writing/write_out.c \
	  src/debug/debug.c

DCSRC = src/decompressor/decompressor.c \
		src/initialization/init_clean.c \
		$(wildcard src/utils/*.c) \
		$(wildcard src/algorithms/*.c)



HDR = src/compression/compressor.h \
	  $(wildcard src/algorithms/*.h) \
	  src/debug/debug.h \
	  $(wildcard src/includes/*.h) \
	  src/initialization/init_clean.h \
	  src/parsing/parser.h \
	  $(wildcard src/utils/*.h) \
	  src/writing/write_out.h

DCHDR = src/decompressor/decompressor.h \
		src/initialization/init_clean.h \
		src/includes/types.h \
		$(wildcard src/algorithms/*.h) 




OBJ = $(SRC:%.c=build/%.o)
DCOBJ = $(DCSRC:%.c=dcbuild/%.o)


compressor: $(OBJ) $(HDR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
decompressor: $(DCOBJ) $(DCHDR)
	$(CC) $(DCOBJ) -o $@ $(LDFLAGS)


build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
dcbuild/%.o: %.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -rf build
	rm -f compressor

rmd:
	rm -rf dcbuild
	rm -f decompressor

rmt:
	rm -f tests/*_sf.zip tests/*_hf.zip