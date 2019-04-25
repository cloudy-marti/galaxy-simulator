int number_of_nodes(BodyNode* universe)
{
    if(universe == NULL)
        return 0;

    int result_north_west = number_of_nodes(universe->northWest);
    int result_north_east = number_of_nodes(universe->northEast);
    int result_south_east = number_of_nodes(universe->southEast);
    int result_south_west = number_of_nodes(universe->southWest);

    return 1 + result_north_west + result_north_east + result_south_east + result_south_west;
}

int number_of_bodies(BodyNode* universe)
{
    if(universe == NULL)
        return 0;

    int body_number = 0;

    if(universe->body != NULL)
        body_number = 1;

    int result_north_west = number_of_bodies(universe->northWest);
    int result_north_east = number_of_bodies(universe->northEast);
    int result_south_east = number_of_bodies(universe->southEast);
    int result_south_west = number_of_bodies(universe->southWest);

    return body_number + result_north_west + result_north_east + result_south_east + result_south_west;

}


int verification_insert_function(BodyNode* universe, Body* B)
{
    BodyNode* result= get_leaf_by_position(universe, B);

    if(result->body != NULL)
    {
        printf("Not empty\n");
        return 1;
    }

    insert_body(universe, B);

    if(result->body == B)
    {
        printf("Added body inside universe \n");
        return 1;
    }

    printf("Added body failed\n" );

    return 0;

}

BodyNode* fake_universe_debug_one_body()
{
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

void print_point(Point* point)
{
    if(point == NULL)
        printf("print_point : this point is NULL \n");

    printf("point->x : %d\n",point->x);
    printf("point->y : %d\n",point->y);

}

void print_bound(Bound* bound)
{
    if(bound == NULL)
        printf("print_bound : this bound is NULL \n");

    if(bound->northWest == NULL || bound->southEast == NULL)
        printf("print_bound : northWest or/and southEast is/are NULL \n");

    printf("-------northWest bound------\n");
    print_point(bound->northWest);
    printf("-------southEast bound------\n");
    print_point(bound->southEast);
}

void print_body(Body* body)
{
    if(body == NULL)
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

    if(has_body(node))
    {
        print_body(node->body);
    }
    else
    {
        printf("No Body inside this node\n");
    }

    printf("-----bound-----\n");
    if(node->bound != NULL)
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

        int result = number_of_bodynode(node);

        int result1 = number_of_bodies(node);

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

int stats_on_node_plus_one(BodyNode* node)
{
    if(node == NULL)
    {
        printf("stats_on_node_plus_one : node is NULL\n");
        return 0;
    }

    if(node->northWest == NULL ||
        node->northEast == NULL || 
        node->southEast == NULL || 
        node->southWest == NULL)
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
