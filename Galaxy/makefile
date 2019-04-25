### Makefile of Galaxy Project ###

CC=gcc
CFLAGS=-Wall -ansi -std=c99 -g
OBJ=$(OBJPATH)physics.o $(OBJPATH)galaxy.o $(OBJPATH)graphic.o $(OBJPATH)galaxy_manager.o $(OBJPATH)quadtree.o $(OBJPATH)quadtree_debug.o $(OBJPATH)visualtree.o
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

$(OBJPATH)galaxy_manager.o: $(SRCPATH)galaxy_manager.c
	$(CC) -c $(SRCPATH)galaxy_manager.c -o $(OBJPATH)galaxy_manager.o $(CFLAGS) -lMLV

$(OBJPATH)quadtree.o: $(SRCPATH)quadtree.c
	$(CC) -c $(SRCPATH)quadtree.c -o $(OBJPATH)quadtree.o $(CFLAGS) -lMLV

$(OBJPATH)physics.o: $(SRCPATH)physics.c
	$(CC) -c $(SRCPATH)physics.c -o $(OBJPATH)physics.o $(CFLAGS) -lMLV

$(OBJPATH)graphic.o: $(SRCPATH)graphic.c
	$(CC) -c $(SRCPATH)graphic.c -o $(OBJPATH)graphic.o $(CFLAGS) -lMLV

$(OBJPATH)quadtree_debug.o: $(SRCPATH)quadtree_debug.c
	$(CC) -c $(SRCPATH)quadtree_debug.c -o $(OBJPATH)quadtree_debug.o $(CFLAGS) -lMLV

$(OBJPATH)visualtree.o: $(SRCPATH)visualtree.c
	$(CC) -c $(SRCPATH)visualtree.c -o $(OBJPATH)visualtree.o $(CFLAGS) -lMLV

clean:
	rm -f $(OBJPATH)$(OBJ)
	rm -f bin/galaxy