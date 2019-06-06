#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/physics.h"
#include "../headers/graphic.h"
#include "../headers/quadtree.h"

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

Galaxy* create_galaxy(int numberOfBodies, double region)
{
	Galaxy* galaxy = (Galaxy*)malloc(sizeof(Galaxy));

	if(galaxy == NULL)
		return NULL;

	galaxy->numberOfBodies = numberOfBodies;
	galaxy->region = region;

	galaxy->bodies = (Body**)malloc(numberOfBodies*sizeof(Body*));

	if(galaxy->bodies == NULL)
		return NULL;

	int i;
	for(i = 0; i < numberOfBodies; ++i)
		galaxy->bodies[i] = NULL;

	galaxy->universe = NULL;

	return galaxy;
}

Bound* create_bound(Point* northWest, Point* southEast)
{
    Bound* bound = (Bound*)malloc(sizeof(Bound));

    bound->northWest = northWest;
    bound->southEast = southEast;

    return bound;
}

BodyNode* create_node(Bound* bound)
{
    BodyNode* node = (BodyNode*)malloc(sizeof(BodyNode));

    node->body = NULL;
    node->bound = bound;

    int x, y;

    x = (bound->northWest->x + bound->southEast->x) / 2;
    y = (bound->northWest->y + bound->southEast->y) / 2;

    node->massCenter = create_point(x, y);
    node->mass = 0.0f;

    node->northEast = NULL;
    node->northWest = NULL;
    node->southEast = NULL;
    node->southWest = NULL;

    return node;
}

BodyNode* create_universe(double region)
{
    Point* northWest = create_point(-region, -region);
    Point* southEast = create_point(region, region);

    Bound* universeBound = create_bound(northWest, southEast);

    BodyNode* universe = create_node(universeBound);

    return universe;
}

Galaxy* galaxy_reader(const char* fileName)
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

	int i;
	double px, py, vx, vy, mass;

	Galaxy* galaxy = create_galaxy(number, region);

	if(galaxy == NULL)
		return NULL;

	Body* newBody = NULL;

	for(i = 0; i < number; i++)
	{
		fscanf(file, "%lf %lf %lf %lf %lf", &px, &py, &vx, &vy, &mass);

		newBody = create_body(px, py, vx, vy, mass);
		if(newBody == NULL)
			return NULL;

		galaxy->bodies[i] = newBody;
	}

	return galaxy;
}

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

    free(node);
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

void free_galaxy(Galaxy* galaxy)
{
	int i;
	for(i = 0; i < galaxy->numberOfBodies; ++i)
		free_body(galaxy->bodies[i]);

	free(galaxy->bodies);
	free_quadtree(galaxy->universe);

	free(galaxy);
}
