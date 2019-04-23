#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"

BodyNode* create_quadtree(Body* body, Bound* bound)
{
	BodyNode* node = (BodyNode*)malloc(sizeof(BodyNode));

	node->body = body;
	node->bound = bound;

	
}