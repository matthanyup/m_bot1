

CC:=/usr/bin/gcc
CFLAGS := -g -std=c99

.PHONY: all
all: movement sharedLibs

.PHONY: clean
clean: cleanAll

movement.o: movement.c
	gcc $(CFLAGS) -c $^ -o $@

gpio.o: gpio.c
	gcc $(CFLAGS) -c $^ -o $@

movement: movement.o gpio.o 
	gcc $(CFLAGS) $^ -lm -o $@

.PHONY: sharedLibs
	mkdir -p sharedLibs
	gcc $(CFLAGS) -shared -fPIC -o sharedLibs/movementLib.so movement.c  gpio.c

cleanAll: 
	@rm -f movement movement.o gpio.o sharedLibs/* 


