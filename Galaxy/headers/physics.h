#ifndef __TWO_BODIES_H__
#define __TWO_BODIES_H__

/*!
 * \file two_bodies.h
 * \brief Struct and function prototypes of two_bodies.c
 * \author Marti Emilie & Soustre Ludovic
 * \version 0.1
 */

#include "../headers/galaxy.h"
#include "../headers/graphic.h"

#define C 1e4

/**
 * Function that contains the main instructions for two rotating bodies
 */
void two_bodies(Galaxy* galaxy);

void all_bodies(Galaxy* galaxy);

void update_force(Body* B1, Body* B2);

void update_position(Body* body);

void update_velocity(Body* body);

#endif