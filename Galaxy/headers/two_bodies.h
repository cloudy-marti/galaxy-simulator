#ifndef __TWO_BODIES_H__
#define __TWO_BODIES_H__

/*!
 * \file two_bodies.h
 * \brief Struct and function prototypes of two_bodies.c
 * \author Marti Emilie & Soustre Ludovic
 * \version 0.1
 */
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define WIDTH_OF_REGION 4e4

#define G  6.674e-11 /*!< the gravitational constant */
#define dt 0.1       /*!< time step */

/**
 * \struct Body
 * \brief Physic body with a position, a velocity and a mass.
 *
 * This is a body to simulate physics.
 */
typedef struct _body
{
    double px;   /*!< x position */
    double py;   /*!< y position */
    double vx;   /*!< x velocity */
    double vy;   /*!< y velocity */
    double fx;   /*!< x force */
    double fy;   /*!< y force */
    double mass; /*!< mass */
} Body;

void draw_body(Body *B);

#endif