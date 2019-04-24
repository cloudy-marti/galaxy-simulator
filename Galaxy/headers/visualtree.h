#ifndef VISUALTREE_H
#define VISUALTREE_H

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"

/*
 * Open a file current-tree.dot, write the DOT code for a tree t,
 * and convert the .dot-file to a pdf.
 */
void write_tree(BodyNode *B);
void write_leaf_debug_add_leaf(BodyNode *B);

#endif /* VISUALTREE_H */
