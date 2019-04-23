/**
 * \file twi_bodies.c
 * \brief Will create two bodies and make them rotate around each other.
 * \author Marti Emilie & Soustre Ludovic
 * \version 0.1
 * \date April 16th 2019
 *
 * Test programm given by M.Thapper to begin the project.
 * Two bodies are created and rotate around each other.
 *
 */

#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/two_bodies.h"
#include "../headers/galaxy.h"
#include "../headers/graphic.h"

void two_bodies(Galaxy* galaxy)
{
    Body* B1 = galaxy->bodies[0];
    Body* B2 = galaxy->bodies[1];

    double region = galaxy->region;

    double t = 0.0;
    
    while (1)
    {
        double dx, dy, dist;
        
        /* compute the gravitational forces */

        /* compute the vector from B1 to B2 and the distance */
        dx = B2->px-B1->px;
        dy = B2->py-B1->py;
        dist = sqrt(dx*dx+dy*dy); /* distance between B1 and B2 */

        /* compute the gravitational force acting on B1 from B2 */
        B1->fx = (G*B1->mass*B2->mass/(dist*dist))*(dx/dist); 
        B1->fy = (G*B1->mass*B2->mass/(dist*dist))*(dy/dist); 

        /* compute the vector from B2 to B1 and the distance */
        dx = B1->px-B2->px;
        dy = B1->py-B2->py;
        dist = sqrt(dx*dx+dy*dy);

        /* compute the gravitational force acting on B2 from B1 */
        B2->fx = (G*B1->mass*B2->mass/(dist*dist))*(dx/dist); 
        B2->fy = (G*B1->mass*B2->mass/(dist*dist))*(dy/dist); 

        /* compute new velocities and positions */

        /* compute B1's new velocity */
        B1->vx += dt*B1->fx/B1->mass;
        B1->vy += dt*B1->fy/B1->mass;
        /* compute B1's new position */
        B1->px += dt*B1->vx;
        B1->py += dt*B1->vy;

        /* compute B2's new velocity */
        B2->vx += dt*B2->fx/B2->mass;
        B2->vy += dt*B2->fy/B2->mass;
        /* compute B2's new position */
        B2->px += dt*B2->vx;
        B2->py += dt*B2->vy;

        /* draw */
        MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
        draw_body(B1, region);
        draw_body(B2, region);
        MLV_update_window();

        /* increment time */
        t += dt;
        MLV_wait_milliseconds(20);
    }
}

void all_bodies(Galaxy* galaxy)
{
    double t = 0.0;

    int i, j;
    
    while (1)
    {
        for(i = 0; i < galaxy->numberOfBodies; i++)
        {
            galaxy->bodies[i]->fx = 0.0f;
            galaxy->bodies[i]->fy = 0.0f;

            for(j = 0; j < galaxy->numberOfBodies; j++)
                if(i != j)
                    update_force(galaxy->bodies[i], galaxy->bodies[j]);

            update_position(galaxy->bodies[i]);
        }

        MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
        draw_bodies(galaxy);
        
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