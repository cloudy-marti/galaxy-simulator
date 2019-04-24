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
    {
        currentLeaf->body = newBody;
        currentLeaf->massCenter = create_point(newBody->px, newBody->py);
        currentLeaf->mass = newBody->mass;
    }
    else
    {
        currentLeaf->body = NULL;
        currentLeaf->mass = get_mass(currentLeaf->body->mass, newBody->mass);
        currentLeaf->massCenter = get_mass_center(currentLeaf->body, newBody);

        create_children(currentLeaf, currentLeaf->body, newBody);
    }


    /*Il faut actualiser le noeuf au dessus*/

void create_children(BodyNode* parent, Body* B1, Body B2)
{
    create_Four_BodyNode(parent);
    insert_body(parent,B1);
    insert_body(parent,B2);
}

void create_Four_BodyNode(BodyNode* bodynode){

    bodynode->northWest = create_Body_init(quad_northwest(bodynode));
    bodynode->northEast = create_Body_init(quad_northEast(bodynode));
    bodynode->southEast = create_Body_init(quad_southEast(bodynode));
    bodynode->southWest = create_Body_init(quad_southWest(bodynode));
}

BodyNode* get_leaf_by_position(BodyNode* universe, Body* body)
{
    BodyNode* tempBody = universe;

    while(tempBody != NULL)
    {
        if(is_in_bound(tempBody->bound, body) && !has_children(tempBody))
            return tempBody;
        else
        {
            if(is_in_bound(tempBody->northWest->bound))
                tempBody=tempBody->northWest;
            else if(is_in_bound(tempBody->northEast->bound))
                tempBody=tempBody->northEast;
            else if(is_in_bound(tempBody->southWest->bound))
                tempBody=tempBody->southWest;
            else(is_in_bound(tempBody->southEast->bound))
                tempBody=tempBody->southEast;
        }
    }
    return tempBody;
}

int has_children(BodyNode* node)
{
    if(node->northWest == NULL && node->northWest == NULL && node->southWest == NULL && node->southEast == NULL)
        return 0;
    else
        return 1;
}

/***************************************************************************************/

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
