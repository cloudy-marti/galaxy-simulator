#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/quadtree.h"
#include "../headers/physics.h"

/*****************************************************************************************************/

// void create_four_nodes(BodyNode* quadtree, Body* newBody)
// {
//     bodynode->northWest = create_node();
//     bodynode->northEast = create_node();
//     bodynode->southEast = create_node();
//     bodynode->southWest = create_node();
// }

// void insert_body(BodyNode* quadtree, Body* body)
// {
//     BodyNode* bodynote = infix_path(quadtree, body);

//     if(bodynote->body == NULL)
//     {
//         bodynote->body = body;
//         bodynote->massCenter = create_point(body->px, body->py);
//         bodynote->mass = body->mass;
//     }
//     else
//     {
//         Body* bodyCurrent = bodynote->body;
//         bodynote->body = NULL;
//         create_Four_BodyNode(bodynote);

//         /*Faire des calculs savant pour la mass et masse centre*/
//         insert_region(bodynote,bodyCurrent);
//         insert_region(bodynote, body);
//     }
// }

// BodyNode* infix_path(BodyNode* quadtree,Body B)
// {
//     while(quadtree != NULL)
//     {
//         int distance=quadtree->bound->northWest->x-quadtree->bound->southEast->x;

//         if (B->px<=(quadtree->bound->northWest->x + distance/2)&&B->px<=(quadtree->bound->southEast->x))  /*northWest*/
//             quadtree = quadtree->northWest;
//         else if (B->px<=(quadtree->bound->northWest->x + distance/2)&&B->px>=(quadtree->bound->southEast->x)) /*northEast*/
//             quadtree = quadtree->northEast;
//         else if (B->px>=(quadtree->bound->northWest->x + distance/2)&&B->px>=(quadtree->bound->southEast->x)) /* southWest */
//             quadtree = quadtree->southWest;
//         else/* southEast */
//             quadtree = quadtree->southEast; /**/
//     }
//     return quadtree;
// }

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

/**
 * Free functions
 */