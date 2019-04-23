#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/two_bodies.h"
#include "../headers/galaxy.h"

#define N 50

int main(int argc, char** argv)
{
    display_window();

    int i;

    for(i = 0; i < N; ++i)
    {

    }

    Body* B1 = create_body(1e4, -1e4, 2.5e3, 0.0, 4e21);
    Body* B2 = create_body(-1e4, 1e4, -2.5e3, 0.0, 4e21);

    two_bodies(*B1, *B2);

    free_body(B1);
    free_body(B2);

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

void free_body(Body* body)
{
	free(body);
}

Body* body_reader(const char* fileName, Body* body)
{
	Body* bodyList;

	return bodyList;
}