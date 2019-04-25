#ifndef __QUADTREE_H__
#define __QUADTREE_H__

void insert_body(BodyNode* universe, Body* newBody);
void update_all_nodes(BodyNode* universe, Body* newBody);
void create_children(BodyNode* parent);

BodyNode* get_leaf_by_position(BodyNode* universe, Body* body);
int has_children(BodyNode* node);
int is_in_bound(Bound* bound, Body* body);
int has_children(BodyNode* node);
int has_body(BodyNode* node);

Bound* quad_northWest(Bound* parentBound);
Bound* quad_northEast(Bound* parentBound);
Bound* quad_southEast(Bound* parentBound);
Bound* quad_southWest(Bound* parentBound);

#endif