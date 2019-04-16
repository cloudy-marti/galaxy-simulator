### Makefile of Galaxy Project ###

CC=gcc
CFLAGS=-Wall -ansi -g
OBJ=two_bodies.o
LDFLAGS=-lMLV -lm

all : galaxy clean_obj
	@echo "--------------------------------------------------------------"
	@echo "               Solar System - INFO1 ALgorithm"
	@echo "               Emilie Marti & Ludovic Soustre"
	@echo ""
	@echo "                to execute type: ./galaxy"
	@echo "--------------------------------------------------------------"

galaxy: $(OBJ)
	$(CC) -o ../galaxy $(OBJ) $(LDFLAGS)

two_bodies.o: two_bodies.c
	$(CC) -c two_bodies.c -o two_bodies.o $(CFLAGS) -lMLV

clean_obj:
	rm -f $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f ../galaxy