#include <stdio.h>
#include <stdlib.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/quadtree.h"
#include "../headers/physics.h"

void insert_body(BodyNode* universe, Body* newBody)
{

    BodyNode* currentLeaf = get_leaf_by_position(universe, newBody);

    if(currentLeaf->body == NULL){

        currentLeaf->body = newBody;
    }
    else
    {
        Body* tempBody = currentLeaf->body;

        currentLeaf->body = NULL;
        currentLeaf->mass = get_mass(tempBody->mass, newBody->mass);
        currentLeaf->massCenter = get_mass_center(tempBody, newBody);

        create_children(currentLeaf);

        print_body(newBody);

        /*print_bodynode(currentLeaf);*/
        getchar();


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

    if(universe == NULL || body==NULL)
        return NULL;

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

    return NULL;
}

int has_children(BodyNode* node)
{
    if(node->northWest == NULL && node->northEast == NULL && node->southEast == NULL && node->southWest == NULL)
        return 0;
    else
        return 1;
}

int has_body_in_the_node(BodyNode* node)
{
    if(node->body!=NULL)
        return 1;
    else
        return 0;
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

    x = parentBound->northWest->x;
    y = (parentBound->northWest->y + parentBound->southEast->y) / 2;

    Point* northWest = create_point(x, y);

    /**
     * Create south-east point of the new bound
     */
    y = parentBound->southEast->y;
    x = (parentBound->northWest->x + parentBound->southEast->x) / 2;

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
    y = parentBound->northWest->y;
    x = (parentBound->northWest->x + parentBound->southEast->x) / 2;

    Point* northWest = create_point(x, y);

    /**
     * Create south-east point of the new bound
     */
    y = (parentBound->northWest->x + parentBound->southEast->x) / 2;
    x = parentBound->southEast->y;

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

int number_of_bodynode_in_quadtree(BodyNode* universe){


    if(universe == NULL)
        return 0;

    int result_north_west = number_of_bodynode_in_quadtree(universe->northWest);
    int result_north_east = number_of_bodynode_in_quadtree(universe->northEast);
    int result_south_east = number_of_bodynode_in_quadtree(universe->southEast);
    int result_south_west = number_of_bodynode_in_quadtree(universe->southWest);

    return 1 + result_north_west + result_north_east + result_south_east + result_south_west;
}

int number_of_bodies_in_quadtree(BodyNode* universe){


    if(universe == NULL)
        return 0;


    int nomber_body = 0;
    if(universe->body!=NULL)
    {
        nomber_body = 1;
    }

    int result_north_west = number_of_bodies_in_quadtree(universe->northWest);
    int result_north_east = number_of_bodies_in_quadtree(universe->northEast);
    int result_south_east = number_of_bodies_in_quadtree(universe->southEast);
    int result_south_west = number_of_bodies_in_quadtree(universe->southWest);

    return nomber_body + result_north_west + result_north_east + result_south_east + result_south_west;

}


int verification_insert_function(BodyNode* universe, Body* B)
{
    BodyNode* result= get_leaf_by_position(universe,B);
    if(result->body!=NULL)
    {
        printf("Not empty\n");
        return 1;
    }
    insert_body(universe,B);
    if(result->body==B)
    {
        printf("Added body inside universe \n");
        return 1;
    }
    printf("Added body failed\n" );
    return 0;

}

BodyNode* fake_uniserse_debug_one_body(){

    /*int number = 1;
	double region = 283800000000;*/
    printf("\n\n------------------------------------------------\n");
    printf("-------------Fake Universe creation debug---------------\n");
    printf("------------------------------------------------\n\n");
	BodyNode* universe = create_universe();
    create_children(universe);

    printf("-------------Insert first body-----------------\n");
	Body* newBody = create_body(2, 2, 2, 2, 2);

	verification_insert_function(universe, newBody);

    /*print_bodynode(universe);*/

    printf("--------------Insert second body----------------\n");
	Body* newBody1 = create_body(3, 3, 3, 3, 3);

	insert_body(universe, newBody1);

    printf("--------------Insert third body----------------\n");
    Body* newBody2 = create_body(4, 4, 4, 4, 4);
	verification_insert_function(universe, newBody2);

    printf("--------------Insert fourth body----------------\n");
    Body* newBody3 = create_body(10, 1115, 115, 1225, 5);
	verification_insert_function(universe, newBody3);

    stats_for_one_node(universe);
    getchar();
    print_bodynode(universe);

    printf("------------------------------\n");


    printf("------------------------------\n");

    return universe;

}

void print_point(Point* point){

    if(point==NULL)
        printf("print_point : this point is NULL \n");

    printf("point->x : %d\n",point->x);
    printf("point->y : %d\n",point->y);

}

void print_bound(Bound* bound){

    if(bound==NULL)
        printf("print_bound : this bound is NULL \n");

    if(bound->northWest == NULL || bound->southEast == NULL)
        printf("print_bound : northWest or/and southEast is/are NULL \n");

    printf("-------northWest bound------\n");
    print_point(bound->northWest);
    printf("-------southEast bound------\n");
    print_point(bound->southEast);

}

void print_body(Body* body){

    if(body==NULL)
        printf("print_body : this body is NULL \n");


    printf("test\n" );
    printf("px : %lf\n",body->px );
        printf("test\n" );

    printf("py : %lf\n",body->py );
        printf("test\n" );

    printf("vx : %lf\n",body->vx );
    printf("vy : %lf\n",body->vy );
    printf("fx : %lf\n",body->fx );
    printf("fy : %lf\n",body->fy );
    printf("mass : %lf\n",body->mass );
    printf("test\n" );
}

void print_bodynode(BodyNode* node)
{

    printf("\n-------------print bodynode-------------\n");
    printf("-----body------\n");
    if(has_body_in_the_node(node)==1)
    {
        print_body(node->body);
    }else
    {
        printf("No Body inside this node\n");
    }

    printf("-----bound-----\n");
    if(node->bound!=NULL)
    {
        print_bound(node->bound);
    }
    else
    {
        printf("No bound inside this node ! NOT NORMAL !\n");
    }
    printf("-----mass------\n");
    printf("%lf\n",node->mass);
    printf("-----masscenter------\n");
    print_point(node->massCenter);
    printf("-----stats------\n");
    stats_for_one_node(node);
}

void stats_for_one_node(BodyNode* node)
{

    printf("------------stat----------\n");
    if (has_children(node))
    {
        printf("This node have children\n");

        int result = number_of_bodynode_in_quadtree(node);

    	int result1 = number_of_bodies_in_quadtree(node);

    	printf("The numbers of node below the current node are/is : %d\n",result);

    	printf("The numbers of bodies below this node are %d\n",result1);

        /*stats_on_node_plus_one(node);*/
    }
    else
    {
        if(has_body_in_the_node(node))
        {
            printf("This node has a body\n");
        }
        else
        {
            printf("This node has no body\n");
        }
        printf("This node has no child\n");

    }
}

int stats_on_node_plus_one(BodyNode* node){


    if(node==NULL)
    {
        printf("stats_on_node_plus_one : node is NULL\n");
        return 0;
    }

    if(node->northWest==NULL || node->northEast == NULL || node->southEast == NULL || node->southWest == NULL)
    {
        printf("stats_on_node_plus_one : node son are NULL\n");
        return 0;
    }

    printf("\n--------stats on node+1 for northWest-------\n");
    print_bodynode(node->northWest);
    printf("\n--------stats on node+1 for northEast-------\n");
    print_bodynode(node->northEast);
    printf("\n--------stats on node+1 for southEast-------\n");
    print_bodynode(node->southEast);
    printf("\n--------stats on node+1 for southWest-------\n");
    print_bodynode(node->southWest);

    return 1;

}

/*Ffunction with univer factive et valeur factive */
