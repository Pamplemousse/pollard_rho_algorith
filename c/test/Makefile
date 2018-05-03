SRC_DIR = ../

CFLAGS=-std=c11 -Wall -Wextra -g
CPPFLAGS=-I../include -DDEBUG
LDFLAGS=-lgmp -lm

.PHONY: all clean help

all: test_iteration_basic test_iteration_r_adding_walks test_collision_floyd test_collision_distinguished_points \
	test_distinguished_points test_equation_solver

test_iteration_basic: test_iteration_basic.o $(SRC_DIR)/iteration_basic.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_iteration_r_adding_walks: test_iteration_r_adding_walks.o $(SRC_DIR)/iteration_r_adding_walks.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_collision_floyd: test_collision_floyd.o $(SRC_DIR)/collision_floyd.o $(SRC_DIR)/iteration_basic.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_collision_distinguished_points: test_collision_distinguished_points.o $(SRC_DIR)/collision_distinguished_points.o \
	$(SRC_DIR)/distinguished_points.o $(SRC_DIR)/iteration_basic.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_equation_solver: test_equation_solver.o $(SRC_DIR)/equation_solver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_distinguished_points: test_distinguished_points.o $(SRC_DIR)/distinguished_points.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f *~ test_iteration_basic test_iteration_r_adding_walks test_collision_floyd \
		test_collision_distinguished_points test_equation_solver test_distinguished_point *.o

help:
	@ echo "Usage:"
	@ echo "  make [all]\t\t# build all tests"
	@ echo "  make clean\t\t# clean temporary objects files"
	@ echo "  make help\t\t# print this help"
