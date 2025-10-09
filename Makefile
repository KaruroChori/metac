# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c23

# TinyCC library flag
TCC_LIBS = -Ltcc

# All targets
all: libmetac.so metac

# Build the preprocessor
metac: metac.c libmetac.c
	$(CC) $(CFLAGS) -o $@ $< -ldl

# Build the preprocessor
libmetac.so: libmetac.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $< -Iinclude

# Clean up build artifacts
clean:
	rm -f tcc_server client *.o *.so


.PHONY: all clean

