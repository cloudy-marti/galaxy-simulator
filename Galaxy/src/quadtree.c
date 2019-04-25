#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/quadtree.h"
#include "../headers/physics.h"

// int counter;

void print_bound(Bound* bound)
{
    printf("NW = (%lf, %lf)\tSE = (%lf, %lf)\n", bound->northWest->x, bound->northWest->y, bound->southEast->x, bound->southEast->y );

}

// BodyNode* insert_body(BodyNode* universe, Body* newBody)
// {
//     if(universe == NULL)
//         return universe;

//     if(newBody == NULL)
//         return
// }

void insert_body(BodyNode* universe, Body* newBody)
{
    // printf("hello\n");
    if(universe == NULL)
    {
        printf("get rekt\n");
        return;
    }

    if(!is_in_bound(universe->bound, newBody))
    {
        printf("not in bound\n");
        print_bound(universe->bound);
        return;
    }

    if(has_children(universe))
    {
        update_mass_and_mass_center(universe, newBody);

        BodyNode* currentLeaf = get_leaf_by_position(universe, newBody);

        insert_body(currentLeaf, newBody);
    }
    else if(universe->body == NULL)
    {
        universe->body = newBody;
        update_mass_and_mass_center(universe, newBody);
    }
    else
    {
        create_children(universe);

        Body* tempBody = universe->body;
        universe->body = NULL;

        universe->mass = 0.0f;

        universe->massCenter->x = 0;
        universe->massCenter->y = 0;

        BodyNode* newLeaf = get_leaf_by_position(universe, newBody);
        BodyNode* tempLeaf = get_leaf_by_position(universe, tempBody);

        insert_body(tempLeaf, tempBody);
        insert_body(newLeaf, newBody);
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
    parent->northWest = create_node(quad_northWest(parent->bound));
    parent->northEast = create_node(quad_northEast(parent->bound));
    parent->southEast = create_node(quad_southEast(parent->bound));
    parent->southWest = create_node(quad_southWest(parent->bound));
}

BodyNode* get_leaf_by_position(BodyNode* universe, Body* body)
{
    // counter++;
    // printf("hello %d\n", counter);
    if(universe == NULL)
    {
        printf("not universe\n");
        return NULL;
    }
    if(body == NULL)
    {
        printf("not a body\n");
        return NULL;
    }

    if(!has_children(universe))
    {
        // printf("universe doesnt have children\n");
        return universe;
    }
    else if(is_in_bound(universe->northWest->bound, body))
    {
        // printf("north west\n");
        return universe->northWest;
    }
    else if(is_in_bound(universe->northEast->bound, body))
    {
        // printf("north east\n");
        return universe->northEast;
    }
    else if(is_in_bound(universe->southEast->bound, body))
    {
        // printf("south east\n");
        return universe->southEast;
    }
    else
    {
        // printf("south west\n");
        return universe->southWest;
    }

    //     return currentLeaf;
    // }


    // BodyNode* tempBody = universe;

    // while(tempBody != NULL)
    // {
    //     if(is_in_bound(tempBody->bound, body) && !has_children(tempBody))
    //         return tempBody;
    //     else
    //     {
    //         if(is_in_bound(tempBody->northWest->bound, body))
    //             tempBody = tempBody->northWest;
    //         else if(is_in_bound(tempBody->northEast->bound, body))
    //             tempBody = tempBody->northEast;
    //         else if(is_in_bound(tempBody->southWest->bound, body))
    //             tempBody = tempBody->southWest;
    //         else
    //             tempBody = tempBody->southEast;
    //     }
    // }
    // return tempBody;
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
    int x, y;

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

    print_bound(bound);

    return bound;
}

Bound* quad_northEast(Bound* parentBound)
{
    int x, y;

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
    y = (parentBound->northWest->y + parentBound->southEast->x) / 2;

    Point* southEast = create_point(x, y);

    /**
     * Create bound
     */
    Bound* bound = create_bound(northWest, southEast);

    return bound;
}

Bound* quad_southWest(Bound* parentBound)
{
    int x, y;

    /**
     * Create north-west point of the new bound
     */
    x = parentBound->northWest->x;
    y = (parentBound->northWest->y + parentBound->southEast->y) / 2;

    Point* northWest = create_point(x, y);

    /**
     * Create south-east point of the new bound
     */
    x = (parentBound->southEast->x + parentBound->southEast->x) / 2;
    y = parentBound->southEast->y;

    Point* southEast = create_point(x, y);

    /**
     * Create bound
     */
    Bound* bound = create_bound(northWest, southEast);

    return bound;
}

Bound* quad_southEast(Bound* parentBound)
{
    int x, y;

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

    return bound;
}