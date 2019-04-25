#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void draw_body(Body *B, double region);
void draw_bodies(BodyNode* universe, double region, int type);
void display_window();
void free_window();

void draw_body_northWest(Body *B, double region);
void draw_body_northEast(Body *B, double region);
void draw_body_southEast(Body *B, double region);
void draw_body_southWest(Body *B, double region);

#endif
