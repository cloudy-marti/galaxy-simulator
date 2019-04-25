#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/quadtree.h"
#include "../headers/physics.h"
#include "../headers/quadtree_debug.h"

void insert_body(BodyNode* universe, Body* newBody)
{
    if(universe == NULL)
        return;

    if(!is_in_bound(universe->bound, newBody))
        return;

    if(has_children(universe))
    {
        update_mass_and_mass_center(universe, newBody);

        // if(is_in_bound(universe->northWest->bound, newBody))
        //     insert_body(universe->northWest, newBody);
        // if(is_in_bound(universe->northEast->bound, newBody))
        //     insert_body(universe->northEast, newBody);
        // if(is_in_bound(universe->southEast->bound, newBody))
        //     insert_body(universe->southEast, newBody);
        // if(is_in_bound(universe->southWest->bound, newBody))
        //     insert_body(universe->southWest, newBody);

        BodyNode* currentLeaf = get_leaf_by_position(universe, newBody);

        // if(currentLeaf == universe->northWest)
        //     printf("goind north west\n");
        // else if(currentLeaf == universe->northEast)
        //     printf("going north east\n");
        // else if(currentLeaf == universe->southEast)
        //     printf("going south east\n");
        // else if(currentLeaf == universe->southWest)
        //     printf("going south west\n");
        // else
        //     printf("what\n");

        insert_body(currentLeaf, newBody);
    }
    else
    {
        if(universe->body == NULL)
        {
            universe->body = newBody;
            // update_mass_and_mass_center(universe, newBody);
        }
        else
        {
            create_children(universe);


            universe->mass = 0.0f;

            universe->massCenter->x = 0.0f;
            universe->massCenter->y = 0.0f;

            // BodyNode* newLeaf = get_leaf_by_position(universe, newBody);
            // BodyNode* tempLeaf = get_leaf_by_position(universe, tempBody);

            insert_body(universe, newBody);
            insert_body(universe, universe->body);

            universe->body = NULL;
        }
    }

    // update_all_nodes(universe, newBody);
}

void update_all_nodes(BodyNode* universe, Body* newBody)
{
    if(universe == NULL)
        return;

    if(is_in_bound(universe->bound, newBody) && !has_children(universe))
        update_mass_and_mass_center(universe, newBody);
    else
    {
        update_all_nodes(universe->northWest, newBody);
        update_all_nodes(universe->northEast, newBody);
        update_all_nodes(universe->southEast, newBody);
        update_all_nodes(universe->southWest, newBody);
    }
}

void create_children(BodyNode* parent)
{
    // printf("\nParent bound :\t");
    // print_bound_bis(parent->bound);
    // printf("\n");

    parent->northWest = create_node(quad_northWest(parent->bound));
    parent->northEast = create_node(quad_northEast(parent->bound));
    parent->southEast = create_node(quad_southEast(parent->bound));
    parent->southWest = create_node(quad_southWest(parent->bound));
}

BodyNode* get_leaf_by_position(BodyNode* universe, Body* body)
{
    if(is_in_bound(universe->northWest->bound, body))
        return universe->northWest;
    if(is_in_bound(universe->northEast->bound, body))
        return universe->northEast;
    if(is_in_bound(universe->southEast->bound, body))
        return universe->southEast;
    else
        return universe->southWest;
}

int has_children(BodyNode* node)
{
    if(node->northWest == NULL || node->northEast == NULL || node->southEast == NULL || node->southWest == NULL)
        return 0;
    else
        return 1;
}

int is_in_bound(Bound* bound, Body* body)
{
    if(body->px >= bound->northWest->x && body->px <= bound->southEast->x)
        if(body->py >= bound->northWest->y && body->py <= bound->southEast->y)
            return 1;

    return 0;
}

int has_body(BodyNode* node)
{
    if(node->body == NULL)
        return 0;
    else
        return 1;
}

Bound* quad_northWest(Bound* parentBound)
{
    double x, y;

    /**
     * Create north-west point of the new bound
     */
    x = parentBound->northWest->x;
    y = parentBound->northWest->y;

    Point* northWest = create_point(x, y);

    /**
     * Create south-east point of the new bound
     */
    x = (parentBound->northWest->x + parentBound->southEast->x) / 2;
    y = (parentBound->northWest->y + parentBound->southEast->y) / 2;

    Point* southEast = create_point(x, y);

    /**
     * Create bound
     */
    Bound* bound = create_bound(northWest, southEast);

    // printf("northWest\t");
    // print_bound_bis(bound);

    return bound;
}

Bound* quad_northEast(Bound* parentBound)
{
    double x, y;

    /**
     * Create north-west point of the new bound
     */
    x = (parentBound->northWest->x + parentBound->southEast->x) / 2;
    y = parentBound->northWest->y;

    Point* northWest = create_point(x, y);

    /**
     * Create south-east point of the new bound
     */
    x = parentBound->southEast->x;
    y = (parentBound->northWest->y + parentBound->southEast->y) / 2;

    Point* southEast = create_point(x, y);

    /**
     * Create bound
     */
    Bound* bound = create_bound(northWest, southEast);

    // printf("northEast\t");
    // print_bound_bis(bound);

    return bound;
}

Bound* quad_southEast(Bound* parentBound)
{
    double x, y;

    /**
     * Create north-west point of the new bound
     */
    x = (parentBound->northWest->x + parentBound->southEast->x) / 2;
    y = (parentBound->northWest->y + parentBound->southEast->y) / 2;

    Point* northWest = create_point(x, y);

    /**
     * Create south-east point of the new bound
     */
    x = parentBound->southEast->x;
    y = parentBound->southEast->y;

    Point* southEast = create_point(x, y);

    /**
     * Create bound
     */
    Bound* bound = create_bound(northWest, southEast);

    // printf("southEast\t");
    // print_bound_bis(bound);

    return bound;
}

Bound* quad_southWest(Bound* parentBound)
{
    double x, y;

    /**
     * Create north-west point of the new bound
     */
    x = parentBound->northWest->x;
    y = (parentBound->northWest->y + parentBound->southEast->y) / 2;

    Point* northWest = create_point(x, y);

    /**
     * Create south-east point of the new bound
     */
    x = (parentBound->northWest->x + parentBound->southEast->x) / 2;
    y = parentBound->southEast->y;

    Point* southEast = create_point(x, y);

    /**
     * Create bound
     */
    Bound* bound = create_bound(northWest, southEast);

    // printf("southWest\t");
    // print_bound_bis(bound);

    return bound;
}