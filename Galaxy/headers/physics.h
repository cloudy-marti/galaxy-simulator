#ifndef __PHYSICS_H__
#define __PHYSICS_H__

/*!
 * \file two_bodies.h
 * \brief Struct and function prototypes of two_bodies.c
 * \author Marti Emilie & Soustre Ludovic
 * \version 0.1
 */

#include "../headers/galaxy.h"

#define C 1e4

void update_all_bodies(Galaxy* galaxy);
void update_bodies(Galaxy* galaxy, BodyNode* node);

void update_force(Body* B1, Body* B2);
void update_position(Body* body);
void update_velocity(Body* body);

Point* create_point(double x, double y);
void free_point(Point* point);

double get_mass(double mass1, double mass2);
Point* get_mass_center(Body* B1, Body* B2);

void update_mass_and_mass_center(BodyNode* node, Body* newBody);
void update_forces(BodyNode* universe, BodyNode* currentNode);
void update_gravitational_force(BodyNode* universe, Body* currentBody);
double get_size_of_bound(Bound* bound);
double get_distance(Point* first, Point* second);

#endif