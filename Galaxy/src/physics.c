/**
 * \file physics.c
 * \brief Will update forces and position of the bodies
 * \author Marti Emilie & Soustre Ludovic
 * \version 1.0
 * \date April 16th 2019
 *
 * Test programm given by M.Thapper to begin the project.
 * Two bodies are created and rotate around each other.
 *
 */

#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/galaxy_manager.h"
#include "../headers/galaxy.h"
#include "../headers/graphic.h"
#include "../headers/physics.h"

void update_all_bodies(Galaxy* galaxy)
{
    double t = 0.0;

    /*int i, j;*/

    display_window();

    while(1)
    {
        // for(i = 0; i < galaxy->numberOfBodies; i++)
        // {
        //     galaxy->bodies[i]->fx = 0.0f;
        //     galaxy->bodies[i]->fy = 0.0f;

        //     for(j = 0; j < galaxy->numberOfBodies; j++)
        //         if(i != j)
        //             update_force(galaxy->bodies[i], galaxy->bodies[j]);

        //     update_position(galaxy->bodies[i]);
        // }

        MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
        draw_bodies(galaxy->universe, galaxy->region,0);

        display_informatons_in_windows(galaxy);
        MLV_update_window();

        t += dt;

        MLV_wait_milliseconds(10);
    }
}

void update_force(Body* B1, Body* B2)
{
    double dx, dy, dist;

    dx = B2->px-B1->px;
    dy = B2->py-B1->py;

    dist = sqrt(dx*dx+dy*dy);

    B1->fx += (G*B1->mass*B2->mass/(dist*dist+(C*C)))*(dx/dist);
    B1->fy += (G*B1->mass*B2->mass/(dist*dist+(C*C)))*(dy/dist);
}

void update_velocity(Body* body)
{
    body->vx += dt*body->fx/body->mass;
    body->vy += dt*body->fy/body->mass;
}

void update_position(Body* body)
{
    update_velocity(body);

    body->px += dt*body->vx;
    body->py += dt*body->vy;
}

Point* create_point(int x, int y)
{
    Point* p = (Point*)malloc(sizeof(Point));

    p->x = x;
    p->y = y;


    return p;
}

void free_point(Point* point)
{
    free(point);
}

double get_mass(double mass1, double mass2)
{
    return mass1 + mass2;
}

Point* get_mass_center(Body* B1, Body* B2)
{
    int x, y;

    double totalMass = get_mass(B1->mass, B2->mass);

    x = (int)(((B1->px * B1->mass) + (B2->px * B2->mass)) / totalMass);
    y = (int)(((B1->py * B1->mass) + (B2->py * B2->mass)) / totalMass);

    Point* massCenter = create_point(x, y);

    return massCenter;
}

void update_mass_and_mass_center(BodyNode* node, Body* newBody)
{
    int tempMass = node->mass;

    int x, y;

    x = (node->massCenter->x * tempMass) + (newBody->px * newBody->mass) / node->mass;
    y = (node->massCenter->y * tempMass) + (newBody->py * newBody->mass) / node->mass;

    node->mass += newBody->mass;

    node->massCenter->x = x;
    node->massCenter->y = y;
}
