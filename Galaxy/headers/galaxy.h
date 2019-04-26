#ifndef __GALAXY_H__
#define __GALAXY_H__

#define G  6.674e-11
#define dt 0.1

typedef struct _body
{
    double px;
    double py;
    double vx;
    double vy;
    double fx;
    double fy;
    double mass;
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

typedef struct _galaxy
{
	int numberOfBodies;
	double region;
	BodyNode* universe;
    Body** bodies;
} Galaxy;

/**
 *  -----------------------
 *  |          |          |
 *  |          |          |
 *  |    0     |    1     |     0 = NorthWest
 *  |          |          |
 *  |          |          |     1 = NorthEast
 *  |----------|----------|
 *  |          |          |     2 = SouthEast
 *  |          |          |
 *  |    3     |    2     |     3 = SouthWest
 *  |          |          |
 *  |          |          |
 *  -----------------------
 */

#endif
