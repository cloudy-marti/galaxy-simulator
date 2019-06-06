#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include <time.h>

#include "../headers/galaxy_manager.h"
#include "../headers/galaxy.h"
#include "../headers/graphic.h"
#include "../headers/physics.h"
#include "../headers/quadtree.h"
#include "../headers/visualtree.h"

void update_all_bodies(Galaxy* galaxy)
{
    double t = 0.0;

    int running = 1;

    while(running)
    {
        galaxy->universe = create_universe(galaxy->region);

        int index;

        for(index = 0; index < galaxy->numberOfBodies; index++)
        {
            insert_body(galaxy->universe, galaxy->bodies[index]);
        }

        update_forces(galaxy->universe, galaxy->universe);
        update_bodies(galaxy, galaxy->universe);

        MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
        draw_bodies(galaxy->universe, galaxy->region);

        MLV_update_window();

        t += dt;
        MLV_wait_milliseconds(10);
        //running--;

        free_quadtree(galaxy->universe);
    }
}

void update_all_bodies_debug(Galaxy* galaxy)
{
    double t = 0.0;
    int number_generation = 0;
    int wait = 10;

    int operation_per_second,result_operation_per_second,seconds_one,old_operation_per_second;
    result_operation_per_second = 0;
    time_t seconds_static,seconds_dynamique;

    seconds_static = time(0);

    while(1)
    {
        int index;
        //printf("abc\n");

        galaxy->universe = create_universe(galaxy->region);

        for(index = 0; index < galaxy->numberOfBodies; index++)
        {
            insert_body(galaxy->universe, galaxy->bodies[index]);
        }


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

        update_forces(galaxy->universe, galaxy->universe);
        update_bodies(galaxy, galaxy->universe);



        MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
        draw_bodies(galaxy->universe, galaxy->region);
        display_informatons_in_windows(galaxy,number_generation,result_operation_per_second);

        MLV_update_window();

        t += dt;

        MLV_wait_milliseconds(wait);
        free_quadtree(galaxy->universe);
    }
}

void update_bodies(Galaxy* galaxy, BodyNode* node)
{
    if(node == NULL)
        return;

    update_bodies(galaxy, node->northWest);
    update_bodies(galaxy, node->northEast);
    update_bodies(galaxy, node->southEast);
    update_bodies(galaxy, node->southWest);

    if(node->body == NULL)
        return;

    update_position(node->body);
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

Point* create_point(double x, double y)
{
    Point* point = (Point*)malloc(sizeof(Point));

    point->x = x;
    point->y = y;

    return point;
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
    double x, y;

    double totalMass = get_mass(B1->mass, B2->mass);

    x = (((B1->px * B1->mass) + (B2->px * B2->mass)) / totalMass);
    y = (((B1->py * B1->mass) + (B2->py * B2->mass)) / totalMass);

    Point* massCenter = create_point(x, y);

    return massCenter;
}

void update_mass_and_mass_center(BodyNode* node, Body* newBody)
{
    double tempMass = node->mass;
    node->mass += newBody->mass;

    double x, y;

    x = ((node->massCenter->x * tempMass) + (newBody->px * newBody->mass)) / node->mass;
    y = ((node->massCenter->y * tempMass) + (newBody->py * newBody->mass)) / node->mass;

    node->massCenter->x = x;
    node->massCenter->y = y;
}

void update_forces(BodyNode* universe, BodyNode* currentNode)
{
    if(currentNode == NULL)
        return;

    update_forces(universe, currentNode->northWest);
    update_forces(universe, currentNode->northEast);
    update_forces(universe, currentNode->southEast);
    update_forces(universe, currentNode->southWest);

    if(currentNode->body != NULL)
    {
        currentNode->body->fx = 0.0f;
        currentNode->body->fy = 0.0f;

        update_gravitational_force(universe, currentNode->body);
    }
}

void update_gravitational_force(BodyNode* universe, Body* currentBody)
{
    if(!has_children(universe))
    {
        if(universe->body != NULL)
            if(universe->body != currentBody)
                update_force(currentBody, universe->body);
    }
    else
    {
        Point* bodyPoint = create_point(currentBody->px, currentBody->py);

        double dist = get_distance(universe->massCenter, bodyPoint);
        double size = get_size_of_bound(universe->bound);

        free_point(bodyPoint);

        if(size < dist/2)
        {
            double dx, dy;

            dx = universe->massCenter->x - currentBody->px;
            dy = universe->massCenter->y - currentBody->py;

            currentBody->fx += (G*currentBody->mass*universe->mass/(dist*dist+(C*C)))*(dx/dist);
            currentBody->fy += (G*currentBody->mass*universe->mass/(dist*dist+(C*C)))*(dy/dist);
        }
        else
        {
            update_gravitational_force(universe->northWest, currentBody);
            update_gravitational_force(universe->northEast, currentBody);
            update_gravitational_force(universe->southEast, currentBody);
            update_gravitational_force(universe->southWest, currentBody);
        }
    }
}

double get_size_of_bound(Bound* bound)
{
    return bound->southEast->x - bound->northWest->x;
}

double get_distance(Point* first, Point* second)
{
    double dx, dy, dist;

    dx = first->x - second->x;
    dy = first->y - second->y;

    dist = sqrt((dx*dx) + (dy*dy));

    return dist;
}
