#include <MLV/MLV_all.h>

#include "../headers/galaxy.h"
#include "../headers/graphic.h"

void display_window()
{
    MLV_create_window("Galaxy", "Window", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void draw_body(Body *B, double region)
{
    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/(region/2)));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/(region/2)));

    MLV_draw_filled_circle(window_x, window_y, 5, MLV_COLOR_WHITE);
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

void free_window()
{
	MLV_free_window();
}
