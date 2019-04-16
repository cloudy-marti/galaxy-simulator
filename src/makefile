# Makefile TP 7 INFO1

CC=gcc
CFLAGS=-Wall -ansi -g
OBJ=two_bodies.o
#OBJ=board.o input_manager.o main.o sudoku.o data_reader.o turn_manager.o
LDFLAGS=-lMLV -lm

all : galaxy clean
	@echo "--------------------------------------------------------------"
	@echo "               Solar System - INFO1 ALgorithm"
	@echo "               Emilie Marti & Ludovic Soustre"
	@echo ""
	@echo "                to execute type: ./galaxy"
	@echo "--------------------------------------------------------------"

galaxy: $(OBJ)
	$(CC) -o galaxy $(OBJ) $(LDFLAGS)

two_bodies.o: two_bodies.c
	$(CC) -c two_bodies.c -o two_bodies.o $(CFLAGS) -lMLV

# input_manager.o: input_manager.c
# 	$(CC) -c input_manager.c -o input_manager.o $(CFLAGS) -lMLV

# turn_manager.o: turn_manager.c
# 	$(CC) -c turn_manager.c -o turn_manager.o $(CFLAGS) -lMLV

# sudoku.o: sudoku.c
# 	$(CC) -c sudoku.c $(CFLAGS)

# data_reader.o: data_reader.c
# 	$(CC) -c data_reader.c $(CFLAGS)

# main.o: main.c
# 	$(CC) -c main.c -o main.o $(CFLAGS)

clean:
	rm -f *.o