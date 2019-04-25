#ifndef __GALAXY_MANAGER_H__
#define __GALAXY_MANAGER_H__

#include "../headers/galaxy.h"

Body* create_body(double px, double py, double vx, double vy, double mass);
Bound* create_bound(Point* northWest, Point* southEast);
BodyNode* create_node(Bound* bound);
BodyNode* create_universe(double region);

Galaxy* galaxy_reader(const char* fileName);

void free_body(Body* body);
void free_bound(Bound* bound);
void free_node(BodyNode* node);
void free_quadtree(BodyNode* node);
void free_galaxy(Galaxy* galaxy);

#endif