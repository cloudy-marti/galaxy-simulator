#ifndef __GALAXY_H__
#define __GALAXY_H__

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

#endif