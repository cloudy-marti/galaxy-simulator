#ifndef VISUALTREE_H
#define VISUALTREE_H

#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"

// void write_tree(BodyNode *B);
// void write_leaf_debug_add_leaf(BodyNode *B);
FILE* write_begin(char *name);
void write_end(FILE *f);
void write_node(FILE *f, BodyNode *B);
void write_leaf_empty(FILE *f, BodyNode *B);
void write_leaf_not_empty(FILE *f, BodyNode *B);
void write_child_link(FILE *f, BodyNode *B);
void write_tree_aux(FILE *f, BodyNode *B);
void write_tree(BodyNode *B);

#endif