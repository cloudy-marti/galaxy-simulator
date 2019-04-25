#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/galaxy_manager.h"
#include "../headers/galaxy.h"
#include "../headers/graphic.h"
#include "../headers/physics.h"
#include "../headers/quadtree.h"
#include "../headers/visualtree.h"

void update_all_bodies(Galaxy* galaxy)
{
    double t = 0.0;

    while(1)
    {
        // write_tree(galaxy->universe);

        // update_bodies(galaxy, galaxy->universe);

        MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
        draw_bodies(galaxy->universe, galaxy->region);

        MLV_update_window();

        t += dt;
        MLV_wait_milliseconds(10);
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

    node->body->fx = 0.0f;
    node->body->fy = 0.0f;

    update_gravitational_force(galaxy->universe, node->body);

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

void update_gravitational_force(BodyNode* universe, Body* currentBody)
{
    if(!has_children(universe))
    {
        if(universe->body != currentBody)
            update_force(currentBody, universe->body);
    }
    else
    {
        Point* bodyPoint = create_point(currentBody->px, currentBody->py);

        double dist = get_distance(universe->massCenter, bodyPoint);
        double size = get_size_of_bound(universe->bound);

        if(size < (dist/2))
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
