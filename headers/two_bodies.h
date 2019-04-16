#ifndef __TWO_BODIES_H__
#define __TWO_BODIES_H__

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define WIDTH_OF_REGION 4e4

#define G  6.674e-11 /* the gravitational constant */
#define dt 0.1       /* time step */

typedef struct _body
{
    double px;   /* x position */
    double py;   /* y position */
    double vx;   /* x velocity */
    double vy;   /* y velocity */
    double fx;   /* x force */
    double fy;   /* y force */
    double mass; /* mass */
} body;

#endif