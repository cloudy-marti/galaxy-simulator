#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/two_bodies.h"
#include "../headers/galaxy.h"

#define MAX 50

int main(int argc, char** argv)
{



    /*
    Body* B1 = create_body(1e4, -1e4, 2.5e3, 0.0, 4e21);
    Body* B2 = create_body(-1e4, 1e4, -2.5e3, 0.0, 4e21);

    two_bodies(*B1, *B2);*/

	Galaxy* galaxy = galaxy_reader(argv[1]);

	if(galaxy == NULL)
	{
		printf("file not read ...\n");
		return 0;
	}

	display_window();

	all_bodies(galaxy);

	free_galaxy(galaxy);

	return 0;
}

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

	return galaxy;
}

void free_body(Body* body)
{
	free(body);
}

void free_galaxy(Galaxy* galaxy)
{
	int i;

	for(i = 0; i < galaxy->numberOfBodies; i++)
		free_body(galaxy->bodies[i]);

	free(galaxy->bodies);
	free(galaxy);
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

	for(i = 0; i < number; i++)
	{
		fscanf(file, "%lf %lf %lf %lf %lf", &px, &py, &vx, &vy, &mass);
		galaxy->bodies[i] = create_body(px, py, vx, vy, mass);	
	}

	return galaxy;
}