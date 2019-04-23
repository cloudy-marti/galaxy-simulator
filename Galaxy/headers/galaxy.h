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

typedef struct _galaxy
{
	int numberOfBodies;
	double region;
	Body** bodies;
} Galaxy;

typedef struct _point
{
	int x;
	int y;
} Point;

typedef struct _bound
{
	Point northWest;
	Point southEast;
} Bound;

typedef struct _bodyNode
{
	Body* body;
	Bound* bound;

	double mass;
	Point massCenter;

	struct _bodyNode* northWest;
	struct _bodyNode* northEast;
	struct _bodyNode* southWest;
	struct _bodyNode* southEast;
} BodyNode;

Body* create_body(double px, double py, double vx, double vy, double mass);
Galaxy* create_galaxy(int numberOfBodies, double region);

Galaxy* galaxy_reader(const char* fileName);

void free_body(Body* body);
void free_galaxy(Galaxy* galaxy);

#endif