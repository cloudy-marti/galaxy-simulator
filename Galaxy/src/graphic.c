#include <MLV/MLV_all.h>

#include "../headers/galaxy.h"
#include "../headers/graphic.h"
#include "../headers/galaxy_manager.h"

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

int draw_bodies(BodyNode* universe, double region,int type)
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

    MLV_draw_filled_circle(window_x, window_y, 0.8, MLV_COLOR_GREEN);
}

void draw_body_northEast(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 0.8, MLV_COLOR_BLUE);
}

void draw_body_southEast(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 0.8, MLV_COLOR_PINK);
}

void draw_body_southWest(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 0.8, MLV_COLOR_YELLOW);
}



void display_number_bodies_in_windows(){



}

void display_number_nodes_in_windows(Galaxy* galaxy,MLV_Font* font){

    char text1[50];
    int number_element = number_of_bodynode_in_quadtree(galaxy->universe);
    sprintf(text1, "%d", number_element);
    char text[50]="Numbers of nodes in the quadtree are : ";
    strcat(text, text1);

    MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.91,&text,font,MLV_COLOR_PINK);

    return;


}

int display_number_nodes_total_in_windows(Galaxy* galaxy,MLV_Font* font){

   char text1[50];
   int number_element = galaxy->numberOfBodies;
   sprintf(text1, "%d", number_element);
   char text[50]="Number of bodides in the file are: ";
   strcat(text, text1);

   MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.95,&text,font,MLV_COLOR_PINK);

   return;
}

void display_number_bodies_inside_qt_in_windows(Galaxy* galaxy,MLV_Font* font){


    char text1[50];
    int number_element = number_of_bodies_in_quadtree(galaxy->universe);
    sprintf(text1, "%d", number_element);
    char text[50]="Number of bodies in the quadtree are : ";
    strcat(text, text1);

    MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.93,&text,font,MLV_COLOR_PINK);

    return;


}

void display_quadtree_delimitation(BodyNode* universe){

    if(universe == NULL)
        return;

    display_quadtree_delimitation(universe->northWest);
    display_quadtree_delimitation(universe->northEast);
    display_quadtree_delimitation(universe->southEast);
    display_quadtree_delimitation(universe->southWest);


        int width = (universe->bound->northWest->x + universe->bound->southEast->x);
        int height = (universe->bound->northWest->y + universe->bound->southEast->y);

        printf("test\n" );
        MLV_draw_rectangle(universe->bound->northWest->x,universe->bound->northWest->y,width,height,MLV_COLOR_WHITE);




    return;

}

int display_informatons_in_windows(Galaxy* galaxy){


    MLV_Font* font = MLV_load_font( "data/Magnificent.ttf" , WINDOW_HEIGHT*0.020 );
    if(galaxy==NULL){
        printf("display_informatons_in_windows : universe is NULL\n");
        return 0;
    }
    if(galaxy->numberOfBodies==0){
        printf("display_informatons_in_windows : universe->numberOfBodies is empty\n");
        return 0;
    }

    display_number_bodies_inside_qt_in_windows(galaxy,font);
    display_number_nodes_total_in_windows(galaxy,font);
    display_number_nodes_in_windows(galaxy,font);
    display_quadtree_delimitation(galaxy->universe);

    
    return 1;


}
