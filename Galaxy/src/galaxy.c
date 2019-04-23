#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/two_bodies.h"
#include "../headers/galaxy.h"

#define MAX 50

int main(int argc, char** argv)
{
    display_window();

    

    /*
    Body* B1 = create_body(1e4, -1e4, 2.5e3, 0.0, 4e21);
    Body* B2 = create_body(-1e4, 1e4, -2.5e3, 0.0, 4e21);

    two_bodies(*B1, *B2);*/

    Galaxy* galaxy = body_reader(argv[1]);

    two_bodies(*(galaxy->bodies[0]), *(galaxy->bodies[1]));

    return 0;
}

Body* create_body(double px, double py, double vx, double vy, double mass)
{
	Body* body = (Body*)malloc(sizeof(Body));

	body->px = px;
	body->py = py;

	body->vx = vx;
	body->vy = vy;

	body->fx = 0.0;
	body->fy = 0.0;

	body->mass = mass;

	return body;
}

Galaxy* create_galaxy(int numberOfBodies, double region, Body** bodies)
{
	Galaxy* galaxy = (Galaxy*)malloc(sizeof(Galaxy));

	galaxy->numberOfBodies = numberOfBodies;
	galaxy->region = region;
	galaxy->bodies = bodies;

	return galaxy;
}

void free_body(Body* body)
{
	free(body);
}

Galaxy* body_reader(const char* fileName)
{
	Body** bodyArray = (Body**)malloc(sizeof(Body*));

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

	int i, j;
    double px, py, vx, vy, mass;

    for(i = 0; i < number; ++i)
    {
	    	fscanf(file, "%lf", &px);
	    	fscanf(file, "%lf", &py);
	    	fscanf(file, "%lf", &vx);
	    	fscanf(file, "%lf", &vy);
	    	fscanf(file, "%lf", &mass);

	    	bodyArray[i] = create_body(px, py, vx, vy, mass);	
    }

    Galaxy* galaxy = create_galaxy(number, region, bodyArray);

	return galaxy;
}