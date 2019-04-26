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
#include <time.h>

#include "../headers/galaxy_manager.h"
#include "../headers/galaxy.h"
#include "../headers/graphic.h"
#include "../headers/physics.h"

void update_all_bodies(Galaxy* galaxy)
{
    double t = 0.0;
    int number_generation = 0;
    int wait = 10;

    int operation_per_second,result_operation_per_second,seconds_one,old_operation_per_second;
    result_operation_per_second = 0;
    time_t seconds_static,seconds_dynamique;
    display_window();

    seconds_static = time(0);

    while(1)
    {
        int index;



        seconds_dynamique = time(0);
        seconds_one = seconds_dynamique-seconds_static;

        operation_per_second += 1;
        if(seconds_one>=1)
        {
            seconds_static = time(0);
            old_operation_per_second=result_operation_per_second;
            result_operation_per_second = operation_per_second;
            operation_per_second = 0;
            if(old_operation_per_second-result_operation_per_second > 100 || result_operation_per_second - old_operation_per_second > 100 )
            {
                result_operation_per_second = old_operation_per_second;
            }
        }

        number_generation += 1;

        /*for(index = 0; index < galaxy->numberOfBodies; index++)
        {
            printf("test\n" );

            insert_body(galaxy->universe, galaxy->bodies[index]);
        }*/

        /*update_forces(galaxy->universe, galaxy->universe);
        update_bodies(galaxy, galaxy->universe);*/

        MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
        draw_bodies(galaxy->universe, galaxy->region,0);

        display_informatons_in_windows(galaxy,number_generation,result_operation_per_second);

        MLV_update_window();
        stats_for_one_node(galaxy->universe);

        /*stats_on_node_plus_one(galaxy->universe);*/

        /*free_quadtree(galaxy->universe);*/

        /*stats_for_one_node(galaxy->universe);*/


        /*write_tree(galaxy->universe);*/

        /*Contournerl le rproblème en supprimant complémeent la galaxy ?? */
        /*Faire stat de l'univers pour savoir son état*/

        getchar();

        t += dt;

        MLV_wait_milliseconds(wait);
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
    point->x=0;
    point->y=0;
    point=NULL;
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
