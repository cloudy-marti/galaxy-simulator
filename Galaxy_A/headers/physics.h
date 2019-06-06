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

void update_force(Body* B1, Body* B2);
void update_velocity(Body* body);
void update_position(Body* body);

#endif