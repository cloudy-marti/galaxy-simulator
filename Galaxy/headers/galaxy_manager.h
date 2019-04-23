#ifndef __GALAXY_MANAGER_H__
#define __GALAXY_MANAGER_H__

#include "../headers/galaxy.h"

Body* create_body(double px, double py, double vx, double vy, double mass);

Galaxy* create_galaxy(int numberOfBodies, double region);

Galaxy* galaxy_reader(const char* fileName);

void free_body(Body* body);

void free_galaxy(Galaxy* galaxy);

#endif