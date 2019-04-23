### Makefile of Galaxy Project ###

CC=gcc
CFLAGS=-Wall -ansi -std=c99 -g
OBJ=$(OBJPATH)two_bodies.o $(OBJPATH)galaxy.o $(OBJPATH)graphic.o
OBJPATH=obj/
SRCPATH=src/
LDFLAGS=-lMLV -lm

all : galaxy
	@echo "--------------------------------------------------------------"
	@echo "               Solar System - INFO1 ALgorithm"
	@echo "               Emilie Marti & Ludovic Soustre"
	@echo ""
	@echo "               to execute type: ./bin/galaxy"
	@echo "--------------------------------------------------------------"

galaxy: $(OBJ)
	$(CC) -o bin/galaxy $(OBJ) $(LDFLAGS)

$(OBJPATH)galaxy.o: $(SRCPATH)galaxy.c
	$(CC) -c $(SRCPATH)galaxy.c -o $(OBJPATH)galaxy.o $(CFLAGS) -lMLV

$(OBJPATH)two_bodies.o: $(SRCPATH)two_bodies.c
	$(CC) -c $(SRCPATH)two_bodies.c -o $(OBJPATH)two_bodies.o $(CFLAGS) -lMLV

$(OBJPATH)graphic.o: $(SRCPATH)graphic.c
	$(CC) -c $(SRCPATH)graphic.c -o $(OBJPATH)graphic.o $(CFLAGS) -lMLV

clean:
	rm -f $(OBJPATH)$(OBJ)
	rm -f bin/galaxy