#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/quadtree.h"
#include "../headers/physics.h"

void insert_body(BodyNode* universe, Body* newBody)
{
    BodyNode* currentLeaf = get_leaf_by_position(universe, newBody);

    if(currentLeaf->body == NULL)
        currentLeaf->body = newBody;
    else
    {
        Body* tempBody = currentLeaf->body;

        currentLeaf->body = NULL;
        currentLeaf->mass = get_mass(tempBody->mass, newBody->mass);
        currentLeaf->massCenter = get_mass_center(tempBody, newBody);

        create_children(currentLeaf);

        insert_body(currentLeaf, tempBody);
        insert_body(currentLeaf, newBody);
    }

    update_all_nodes(universe, newBody);
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
    if(universe == NULL)
        return NULL;

    if(is_in_bound(universe->bound, body))
        return universe;

    get_leaf_by_position(universe->northWest, body);
    get_leaf_by_position(universe->northEast, body);
    get_leaf_by_position(universe->southEast, body);
    get_leaf_by_position(universe->southWest, body);

    return universe;

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
    if(node->northWest == NULL && node->northEast == NULL && node->southEast == NULL && node->southWest == NULL)
        return 0;
    else
        return 1;
}

int is_in_bound(Bound* bound, Body* body)
{
    /**
     * Body is within x values of bound
     */
    if(body->px >= bound->northWest->x && body->px <= bound->southEast->x)
        /**
         * Body is within y values of bound
         */
        if(body->py >= bound->northWest->y && body->py <= bound->southEast->y)
            return 1;

    return 0;
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
