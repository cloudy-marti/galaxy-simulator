#ifndef __QUADTREE_H__
#define __QUADTREE_H__

void insert_body(BodyNode* universe, Body* newBody);
void update_all_nodes(BodyNode* universe, Body* newBody);
void create_children(BodyNode* parent);

BodyNode* get_leaf_by_position(BodyNode* universe, Body* body);
int has_children(BodyNode* node);
int is_in_bound(Bound* bound, Body* body);

Bound* quad_northWest(Bound* parentBound);
Bound* quad_northEast(Bound* parentBound);
Bound* quad_southWest(Bound* parentBound);
Bound* quad_southEast(Bound* parentBound);

void debug_with_visualtree(int mode, BodyNode *B);

int verification_insert_function(BodyNode* universe, Body* B);

int number_of_bodynode_in_quadtree(BodyNode* universe);
int number_of_bodies_in_quadtree(BodyNode* universe);

BodyNode* fake_uniserse_debug_one_body();

void print_point(Point* point);
void print_bound(Bound* bound);
void print_body(Body* body);
void print_bodynode(BodyNode* node);

void stats_for_one_node(BodyNode* node);
int stats_on_node_plus_one(BodyNode* node);

int max(int result1, int result2, int result3, int result4);
int dept(BodyNode* node);



#endif
