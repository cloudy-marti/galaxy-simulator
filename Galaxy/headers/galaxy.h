#ifndef __GALAXY_H__
#define __GALAXY_H__

#define G  6.674e-11 /*!< the gravitational constant */
#define dt 0.1       /*!< time step */

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

typedef struct _point
{
	int x;
	int y;
} Point;

typedef struct _bound
{
	Point* northWest;
	Point* southEast;
} Bound;

typedef struct _bodyNode
{
	Body* body;
	Bound* bound;

	double mass;
	Point* massCenter;

	struct _bodyNode* northWest;
	struct _bodyNode* northEast;
	struct _bodyNode* southWest;
	struct _bodyNode* southEast;
} BodyNode;

/**
 *  -----------------------
 *  |          |          |
 *  |          |          |
 *  |    0     |    1     |     0 = NorthWest
 *  |          |          |
 *  |          |          |     1 = NorthEast
 *  |----------|----------|
 *  |          |          |     2 = SouthWest
 *  |          |          |
 *  |    2     |    3     |     3 = SouthEast
 *  |          |          |
 *  |          |          |
 *  -----------------------
 */

#endif