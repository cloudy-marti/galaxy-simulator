#ifndef __QUADTREE_DEBUG_H__
#define __QUADTREE_DEBUG_H__

int number_of_nodes(BodyNode* universe);
int number_of_bodies(BodyNode* universe);

int verification_insert_function(BodyNode* universe, Body* B);
BodyNode* fake_universe_debug_one_body();

void print_point(Point* point);
void print_bound(Bound* bound);
void print_bound_bis(Bound* bound);
void print_body(Body* body);
void print_body_position(Body* body);
void print_bodynode(BodyNode* node);

void stats_for_one_node(BodyNode* node);
int stats_on_node_plus_one(BodyNode* node);

int depth(BodyNode* node);
int max(int result1, int result2, int result3, int result4);

void comparison_between_theoretical_bodies_and_bodies_in_qt(Galaxy* galaxy);

int number_of_bodynode_in_quadtree(BodyNode* universe);
int number_of_bodies_in_quadtree(BodyNode* universe);

#endif