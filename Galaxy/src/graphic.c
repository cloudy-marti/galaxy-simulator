#include <MLV/MLV_all.h>

#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/graphic.h"
#include "../headers/physics.h"
#include "../headers/quadtree_debug.h"

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

void draw_bodies(BodyNode* universe, double region)
{
    if(universe == NULL)
        return;

    draw_bodies(universe->northWest, region);
    draw_bodies(universe->northEast, region);
    draw_bodies(universe->southEast, region);
    draw_bodies(universe->southWest, region);

    if(universe->body != NULL)
    	draw_body(universe->body, region);

    return;
}

void display_number_nodes_in_windows(Galaxy* galaxy,MLV_Font* font)
{
    char text1[50];
    int number_element = number_of_bodynode_in_quadtree(galaxy->universe);
    sprintf(text1, "%d", number_element);
    char text[50]="Number of nodes in the quadtree : ";
    strcat(text, text1);

    MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.91,text,font,MLV_COLOR_PINK);

    return;
}

int display_number_nodes_total_in_windows(Galaxy* galaxy,MLV_Font* font)
{
   char text1[50];
   int number_element = galaxy->numberOfBodies;
   sprintf(text1, "%d", number_element);
   char text[50]="Number of bodies in the file : ";
   strcat(text, text1);

   MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.95,text,font,MLV_COLOR_PINK);

   return 1;
}

void display_number_bodies_inside_qt_in_windows(Galaxy* galaxy,MLV_Font* font)
{
    char text1[50];
    int number_element = number_of_bodies_in_quadtree(galaxy->universe);
    sprintf(text1, "%d", number_element);
    char text[50]="Number of bodies in the quadtree : ";
    strcat(text, text1);

    MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.93,text,font,MLV_COLOR_PINK);

    return;
}

void display_quadtree_delimitation(Galaxy* galaxy,BodyNode* universe)
{

    if(universe == NULL)
        return;

    display_quadtree_delimitation(galaxy,universe->northWest);
    display_quadtree_delimitation(galaxy,universe->northEast);
    display_quadtree_delimitation(galaxy,universe->southEast);
    display_quadtree_delimitation(galaxy,universe->southWest);

    double region = galaxy->region;

    int northWestX = universe->bound->northWest->x;
    int northWestY = universe->bound->northWest->y;
    int southEastX = universe->bound->southEast->x;
    int southEastY = universe->bound->southEast->y;

    int window_nwx = WINDOW_WIDTH*(0.5+0.5*(northWestX/(region/2)));
    int window_nwy = WINDOW_HEIGHT*(0.5+0.5*(northWestY/(region/2)));
    int window_sex = WINDOW_WIDTH*(0.5+0.5*(southEastX/(region/2)));
    int window_sey = WINDOW_HEIGHT*(0.5+0.5*(southEastY/(region/2)));

    int width = window_sex - window_nwx;
    int height = window_sey - window_nwy;

    if(universe->body!=NULL)
    {
        MLV_draw_rectangle(window_nwx,window_nwy,width,height,MLV_COLOR_DARK_GREEN);
    }
    else
    {
        MLV_draw_rectangle(window_nwx,window_nwy,width,height, MLV_COLOR_BEIGE);
    }

    return;
}

int display_informatons_in_windows(Galaxy* galaxy, int number_generation, int operation_per_second, MLV_Font* font)
{
    if(galaxy==NULL){
        printf("display_information_in_windows : universe is NULL\n");
        return 0;
    }
    if(galaxy->numberOfBodies==0){
        printf("display_information_in_windows : universe->numberOfBodies is empty\n");
        return 0;
    }

    display_number_bodies_inside_qt_in_windows(galaxy,font);
    display_number_nodes_total_in_windows(galaxy,font);
    display_number_nodes_in_windows(galaxy,font);
    
    display_quadtree_delimitation(galaxy,galaxy->universe);
    
    display_generation_number(number_generation,font);
    display_operation_per_second(operation_per_second,font);
    display_depth_of_the_quadtree(galaxy->universe,font);
    
    return 1;
}

int display_generation_number(int number_generation,MLV_Font* font)
{
    char text1[50];
    sprintf(text1, "%d", number_generation);
    char text[50]="Number of generation is : ";
    strcat(text, text1);

    MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.89,text,font,MLV_COLOR_PINK);

    return 1;
}

int display_operation_per_second(int operation_per_second,MLV_Font* font)
{
    char text1[50];
    char text[50]="Number of operations per second : ";
    if(operation_per_second!=0){
        sprintf(text1, "%d", operation_per_second);
        strcat(text, text1);
    }

    MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.87,text,font,MLV_COLOR_PINK);

    return 1;
}

int display_depth_of_the_quadtree(BodyNode* universe,MLV_Font* font)
{
    char text1[50];
    int test = depth(universe);

    sprintf(text1, "%d", test);
    char text[50]="The depth in the quadtree is : ";
    strcat(text, text1);

    MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.85,text,font,MLV_COLOR_PINK);

    return 1;
}

void menu(Galaxy* galaxy)
{
    int x,y;

    char text1_1[50]="Galaxy";
    char text2_1[50]="Quadtree";

    int height_value = WINDOW_HEIGHT*0.07;

    int width_value_1 = WINDOW_WIDTH*0.35;
    int width_value_2 = WINDOW_WIDTH*0.55;

    int height_value_size = WINDOW_HEIGHT*0.20;
    int width_value_size = WINDOW_HEIGHT*0.05;

    MLV_Font* font = MLV_load_font( "data/font.ttf" , 20 );

    int i = 0;
    int size = 1000;
    int posX[size], posY[size];
    float sizes[4] = {0.4f, 0.6f, 0.8f, 1.0f};

    for(i = 0; i < size; ++i)
    {
        posX[i] = rand()%WINDOW_WIDTH;
        posY[i] = rand()%WINDOW_HEIGHT;
    }

    while(1)
    {
        MLV_clear_window(MLV_COLOR_BLACK);

        MLV_Color color1 = MLV_COLOR_DODGERBLUE4;
        MLV_Color color2 = MLV_COLOR_DODGERBLUE4;
        
        for(i = 0; i < size; ++i)
        {
            MLV_draw_filled_circle(posX[i], posY[i], sizes[rand()%4], MLV_COLOR_WHITE);
        }
        
        MLV_get_mouse_position(&x,&y);
        
        if(x > height_value && x < height_value + height_value_size &&
            y > width_value_1 && y < width_value_1 + width_value_size)
        {
            if(MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED)
            {
                update_all_bodies(galaxy);
            }
            else
            {
                color1 = MLV_COLOR_DODGERBLUE2;
            }
        }

        if(x > height_value && x < height_value + height_value_size &&
            y > width_value_2 && y < width_value_2 + width_value_size)
        {
            if(MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED)
            {
                update_all_bodies_debug(galaxy);
            }
            else
            {
                color2 = MLV_COLOR_DODGERBLUE2;
            }
        }


        MLV_draw_text_box_with_font(height_value,width_value_1,
                                    WINDOW_HEIGHT*0.20, WINDOW_HEIGHT*0.05,
                                    text1_1, font, 0,
                                    color1, MLV_COLOR_GHOST_WHITE, color1,
                                    MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

        MLV_draw_filled_rectangle(height_value, width_value_1, WINDOW_HEIGHT*0.20, 5, MLV_COLOR_DODGERBLUE);
        MLV_draw_filled_rectangle(height_value, width_value_1, 5, WINDOW_HEIGHT*0.05, MLV_COLOR_DODGERBLUE2);

        MLV_draw_text_box_with_font(height_value,width_value_2,
                                    WINDOW_HEIGHT*0.20, WINDOW_HEIGHT*0.05,
                                    text2_1, font, 0,
                                    color2, MLV_COLOR_GHOST_WHITE, color2,
                                    MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

        MLV_draw_filled_rectangle(height_value, width_value_2, WINDOW_HEIGHT*0.20, 5, MLV_COLOR_DODGERBLUE);
        MLV_draw_filled_rectangle(height_value, width_value_2, 5, WINDOW_HEIGHT*0.05, MLV_COLOR_DODGERBLUE2);

        MLV_update_window();
    }

    MLV_free_font(font);
    
    return;
}

void free_window()
{
    MLV_free_window();
}
