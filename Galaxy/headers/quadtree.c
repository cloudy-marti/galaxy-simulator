#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"

// BodyNode* create_universe(Body* body, Bound* bound)
// {
// 	BodyNode* node = (BodyNode*)malloc(sizeof(BodyNode));

// 	node->body = body;
// 	node->bound = bound;

// 	node->mass = body->mass;

// 	node->massCenter->northWest->x = 0;
// 	node->massCenter->northWest->y = 0;

// 	node->massCenter->northWest->x = 0;
// 	node->massCenter->northWest->y = 0;
// }

int main(int argc, char** argv)
{

	/**
	 * Creating root of quadtree -> meaning the universe
	 */
	Point* northWest = (Point*)malloc(sizeof(Point));
	northWest->x = 0;
	northWest->y = 0;

	Point* southEast = (Point*)malloc(sizeof(Point));
	southEast->x = 800;
	southEast->y = 800;

	Bound* universeBound = (Bound*)malloc(sizeof(Bound));
	universeBound->northWest = northWest;
	universeBound->southEast = southEast;

	BodyNode* universe = (BodyNode*)malloc(sizeof(BodyNode));

	universe->body = NULL;
	universe->bound = universeBound;

	universe->mass = 0.0f;

	universe->massCenter->x = 400;
	universe->massCenter->y = 400;

	universe->northWest = NULL;
	universe->northEast = NULL;
	universe->southWest = NULL;
	universe->southEast = NULL;

	insert_body();
}

void insert_body(BodyNode* quadtree, Body* body)
{
	
}