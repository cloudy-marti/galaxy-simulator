#include <MLV/MLV_all.h>

#include "../headers/galaxy.h"
#include "../headers/graphic.h"
#include "../headers/galaxy_manager.h

void display_window()
{
    MLV_create_window("Galaxy", "Window", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void draw_body(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 0.8, MLV_COLOR_WHITE);
}

void draw_bodies(BodyNode* universe, double region,int type)
{
    if(universe == NULL)
        return;

    int debug = 1;
    if(debug==0){
        draw_bodies(universe->northWest, region,0);
        draw_bodies(universe->northEast, region,0);
        draw_bodies(universe->southEast, region,0);
        draw_bodies(universe->southWest, region,0);

        if(universe->body != NULL)
        	draw_body(universe->body, region);
    }
    else
    {
        draw_bodies(universe->northWest, region,1);
        draw_bodies(universe->northEast, region,2);
        draw_bodies(universe->southEast, region,3);
        draw_bodies(universe->southWest, region,4);

        if(type==0)
            if(universe->body != NULL)
                draw_body(universe->body,region);

        if(type==1)
            if(universe->body != NULL)
                draw_body_northWest(universe->body,region);
        if(type==2)
            if(universe->body != NULL)
                draw_body_northEast(universe->body,region);

        if(type==3)
            if(universe->body != NULL)
                draw_body_southEast(universe->body,region);

        if(type==4)
            if(universe->body != NULL)
                draw_body_southWest(universe->body,region);

    }
    return;
}

void free_window()
{
	MLV_free_window();
}


void draw_body_northWest(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 2, MLV_COLOR_GREEN);
}

void draw_body_northEast(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 2, MLV_COLOR_BLUE);
}

void draw_body_southEast(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 2, MLV_COLOR_PINK);
}

void draw_body_southWest(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 2, MLV_COLOR_YELLOW);
}



void display_number_bodies_in_windows(){



}

void display_number_nodes_in_windows(){



}

void display_number_nodes_total_in_windows(){



}

void display_number_bodies_inside_qt_in_windows(){



}

void display_quadtree_delimitation(){


    
}
