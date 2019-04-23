#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WIDTH_OF_REGION 6e4

void draw_body(Body *B, double region);
void draw_bodies(Galaxy* galaxy);
void display_window();

#endif