#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/physics.h"
#include "../headers/graphic.h"

Body* create_body(double px, double py, double vx, double vy, double mass)
{
	Body* body = (Body*)malloc(sizeof(Body));

	if(body == NULL)
		return NULL;

	body->px = px;
	body->py = py;

	body->vx = vx;
	body->vy = vy;

	body->fx = 0.0f;
	body->fy = 0.0f;

	body->mass = mass;

	return body;
}

Bound* create_bound(Point* northWest, Point* southEast)
{
    Bound* bound = (Bound*)malloc(sizeof(Bound));

    bound->northWest = northWest;
    bound->southEast = southEast;

    return bound;
}

BodyNode* create_node(Bound* bound, Point* massCenter)
{
    BodyNode* node = (BodyNode*)malloc(sizeof(BodyNode));

    node->bound = bound;

    node->mass = 0.0f;
    node->massCenter = massCenter;

    node->northEast = NULL;
    node->northWest = NULL;
    node->southEast = NULL;
    node->southWest = NULL;

    return node;
}

BodyNode* create_universe()
{
    Point* northWest = create_point(0, 0);
    Point* southEast = create_point(WINDOW_WIDTH, WINDOW_HEIGHT);

    Bound* universeBound = create_bound(northWest, southEast);

    BodyNode* universe = create_node(universeBound, NULL);

    return universe;
}

BodyNode* galaxy_reader(const char* fileName)
{
	FILE* file;
	file = fopen(fileName, "r");

	if(file == NULL)
	{
		fprintf(stderr, "File \"%s\" not found ...\n", fileName);
		return NULL;
	}
	
	int number;
	double region;

	fscanf(file, "%d", &number);
	fscanf(file, "%lf", &region);

	/**
	 * needed : to be uncommented (now just to avoid warnings)
	 */
	// double px, py, vx, vy, mass;

	BodyNode* galaxy = create_universe();

	/**
	 * TO DO :
	 * fscanf the file and fill the universe
	 */

	return galaxy;
}
// Galaxy* galaxy_reader(const char* fileName)
// {



// 	Galaxy* galaxy = create_galaxy(number, region);	

// 	for(i = 0; i < number; i++)
// 	{
// 		fscanf(file, "%lf %lf %lf %lf %lf", &px, &py, &vx, &vy, &mass);
// 		galaxy->bodies[i] = create_body(px, py, vx, vy, mass);	
// 	}

// 	return galaxy;
// }

void free_body(Body* body)
{
	free(body);
}

void free_bound(Bound* bound)
{
    free_point(bound->northWest);
    free_point(bound->southEast);
    
    free(bound);
}

void free_node(BodyNode* node)
{
    free_point(node->massCenter);
    free_bound(node->bound);

    if(node->body != NULL)
    	free_body(node->body);
}

void free_quadtree(BodyNode* node)
{
    if(node == NULL)
        return;

    free_quadtree(node->northWest);
    free_quadtree(node->northEast);
    free_quadtree(node->southEast);
    free_quadtree(node->southWest);

    free_node(node);

    return;
}
