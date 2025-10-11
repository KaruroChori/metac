# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c23

# TinyCC library flag
TCC_LIBS = -Ltcc

# All targets
all: libmetac.so metac example

# Build the preprocessor
metac: src/metac.c src/libmetac.c
	$(CC) $(CFLAGS) -o $@ $< -ldl

# Build the preprocessor
libmetac.so: src/libmetac.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $< -Iinclude

example: libmetac.so metac
	./metac --gen-makefile ./example/app.json -o ./example/Makefile

# Clean up build artifacts
clean:
	rm -f metac *.o *.so


.PHONY: all clean

