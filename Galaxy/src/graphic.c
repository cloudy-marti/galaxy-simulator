#include <MLV/MLV_all.h>

#include "../headers/galaxy.h"
#include "../headers/graphic.h"

/**
 * \fn void draw_body(body *B)
 * \brief Drawing function of a corpus.
 *
 * \param Body to be drawn.
 * \return Void function doesn't return anything.
 */
void draw_body(Body *B, double region)
{
	
	printf("position x = %.5e\ty = %.5e\n", B->px, B->py);
	

    int window_x = WINDOW_WIDTH*(0.5+0.5*(B->px/region));
    int window_y = WINDOW_HEIGHT*(0.5+0.5*(B->py/region));

    MLV_draw_filled_circle(window_x, window_y, 10, MLV_COLOR_WHITE);
}

void display_window()
{
	/* Open the window */
    MLV_create_window("Galaxy", "Window", WINDOW_WIDTH, WINDOW_HEIGHT);
}