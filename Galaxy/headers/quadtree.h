#ifndef __QUADTREE_H__
#define __QUADTREE_H__

int is_in_bound(Bound* bound, Body* body);

Bound* quad_northWest(Bound* parentBound);
Bound* quad_northEast(Bound* parentBound);
Bound* quad_southWest(Bound* parentBound);
Bound* quad_southEast(Bound* parentBound);

#endif