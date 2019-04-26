#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/quadtree.h"
#include "../headers/physics.h"
#include "../headers/visualtree.h"


void insert_bodyi(BodyNode* universe, Body* newBody)
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

        /*print_body(newBody);*/

        /*print_bodynode(currentLeaf);*/
        insert_body(currentLeaf, tempBody);
        insert_body(currentLeaf, newBody);
    }

    update_all_nodes(universe, newBody);
}

void insert_body(BodyNode* universe, Body* newBody)
{
    if(universe == NULL)
    {
        // printf("get rekt\n");
        return;
    }

    else if(!is_in_bound(universe->bound, newBody))
    {
         /*printf("not in bound\n");*/
    }

    else if(has_children(universe))
    {
        // printf("node has children\n");
        update_mass_and_mass_center(universe, newBody);

        BodyNode* currentLeaf = get_leaf_by_position(universe, newBody);

        insert_body(currentLeaf, newBody);
    }
    else if(universe->body == NULL)
    {
        // printf("leaf has no body\n");
        universe->body = newBody;
        update_mass_and_mass_center(universe, newBody);
    }
    else if(universe->body != NULL)
    {
        // printf("leaf has a body\n");
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
    else
        return;

    // printf("bye\n");

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

    if(universe==NULL)
    {
        printf("verification_insert_function : universe is NULL\n");
        return NULL;
    }

    if(body==NULL)
    {
        printf("verification_insert_function : Body is NULL\n");
        return NULL;
    }

    if(is_in_bound(universe->northWest->bound, body))
    {
        return universe->northWest;

    }
    if(is_in_bound(universe->northEast->bound, body))
    {
        return universe->northEast;
    }
    if(is_in_bound(universe->southEast->bound, body))
    {
        return universe->southEast;
    }
    else
    {
        return universe->southWest;
    }


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
    if(bound==NULL )
    {
        printf("is_in_bound : bound is NULL\n");
        return -1;
    }

    if(body==NULL)
    {
        printf("is_in_bound : body is NULL\n");
        return -1;
    }


     if(body->px >= bound->northWest->x && body->px <= bound->southEast->x)
        if(body->py >= bound->northWest->y && body->py <= bound->southEast->y)
            return 1;

    return 0;
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

    if(universe==NULL)
    {
        printf("verification_insert_function : universe is NULL\n");
        return 0;
    }

    if(B==NULL)
    {
        printf("verification_insert_function : Body is NULL\n");
        return 0;
    }
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

    /*int number = 1;*/
	double region = 200;
    int number = 1;
    printf("\n\n------------------------------------------------\n");
    printf("-------------Fake Universe creation debug---------------\n");
    printf("------------------------------------------------\n\n");
	BodyNode* universe = create_universe(region);
    Galaxy* galaxy = create_galaxy(number, region);
    galaxy->universe=universe;


    /*create_children(universe);*/


    printf("-------------Insert first body NW-----------------\n");
    double b1_px = -100;
    double b1_py = -100;
    double b1_vx = 1;
    double b1_vy = 1;
    double mass = 1;


	Body* newBody = create_body(b1_px, b1_py, b1_vx, b1_vy, mass);
    insert_body(universe, newBody);
	/*verification_insert_function(universe, newBody);*/



    /*printf("--------------Insert second body NE----------------\n");
	Body* newBody1 = create_body(3, 3, 3, 3, 3);*/



    /*printf("--------------Insert third body SE----------------\n");
    Body* newBody2 = create_body(4, 4, 4, 4, 4);
	verification_insert_function(universe, newBody2);

    printf("--------------Insert fourth body SW----------------\n");
    Body* newBody3 = create_body(10, 1115, 115, 1225, 5);


	verification_insert_function(universe, newBody3);

    stats_for_one_node(universe);
    getchar();
    print_bodynode(universe);*/


    printf("--------------Insert random body----------------\n");

    /*srand(time(0));
    int i=0;*/
    /*for(i=0;i<number;i++){

        double value_px = (int) rand() % (int)region;

        double value_py = (int) rand() % (int) region;
        double value_fx =  rand() % (int)region;
        double value_fy =  rand() % (int)region;
        double value_mass =  rand() % (int)region;

        Body* Body = create_body(value_px,value_py,value_fx,value_fy,value_mass);
    	verification_insert_function(universe, Body);
        printf(" %f ", value_px);
    }*/
    write_tree(universe);
    stats_for_one_node(universe);

    printf("------------------------------\n");

    update_all_bodies(galaxy);


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

    printf("px : %lf\n",body->px );
    printf("py : %lf\n",body->py );
    printf("vx : %lf\n",body->vx );
    printf("vy : %lf\n",body->vy );
    printf("fx : %lf\n",body->fx );
    printf("fy : %lf\n",body->fy );
    printf("mass : %lf\n",body->mass );
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


int dept(BodyNode* node)
{
    if(node==NULL)
        return 0;

    int result_nw = dept(node->northWest);
    int result_ne = dept(node->northEast);
    int result_se = dept(node->southEast);
    int result_sw = dept(node->southWest);

    int result = max(result_nw,result_ne,result_se,result_sw);

    return result + 1;
}


int max(int result1, int result2, int result3, int result4)
{
    if(result1>=result2 && result1>=result3 && result1>=result4)
    {
        return result1;
    }
    if(result2>=result1 && result2>=result3 && result2>=result4)
    {
        return result2;
    }
    if(result3>=result1 && result3>=result2 && result3>=result4)
    {
        return result3;
    }
    if(result4>=result1 && result4>=result2 && result4>=result3)
    {
        return result4;
    }
}


void comparaison_between_theorique_bodie_and_bodies_in_qt(Galaxy* galaxy){

    int result_qt=number_of_bodies_in_quadtree(galaxy->universe);

    if(galaxy->numberOfBodies!=result_qt){
        printf("Erreur : galaxy->numberOfBodies != number_of_bodies_in_quadtree \n");
    }
}
