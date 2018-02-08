SRC_DIR = ../

CFLAGS=-std=c11 -Wall -Wextra -g
CPPFLAGS=-I../include -DDEBUG
LDFLAGS=-lgmp

.PHONY: all clean help

all: test_iteration test_collision

test_iteration: test_iteration.o $(SRC_DIR)/iteration.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_collision: test_collision.o $(SRC_DIR)/collision.o $(SRC_DIR)/iteration.o 
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f *~ test_iteration test_collision *.o

help:
	@ echo "Usage:"
	@ echo "  make [all]\t\t# build all tests"
	@ echo "  make clean\t\t# clean temporary objects files"
	@ echo "  make help\t\t# print this help"
