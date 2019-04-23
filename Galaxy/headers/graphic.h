#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void draw_body(Body *B, double region);
void draw_bodies(Galaxy* galaxy);
void display_window();
void free_window();

#endif