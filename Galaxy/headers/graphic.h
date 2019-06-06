#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void draw_body(Body *B, double region);
void draw_bodies(BodyNode* universe, double region);
void display_window();
void free_window();

void draw_body_northWest(Body *B, double region);
void draw_body_northEast(Body *B, double region);
void draw_body_southEast(Body *B, double region);
void draw_body_southWest(Body *B, double region);



void display_number_nodes_in_windows(Galaxy* galaxy,MLV_Font* font);
int display_number_nodes_total_in_windows(Galaxy* galaxy,MLV_Font* font);
void display_number_bodies_inside_qt_in_windows(Galaxy* galaxy,MLV_Font* font);
void display_quadtree_delimitation(Galaxy* galaxy,BodyNode* universe);
int display_informatons_in_windows(Galaxy* galaxy,int number_generation, int operation_per_second);
int display_generation_number(int number_generation,MLV_Font* font);
int display_operation_per_second(int operation_per_second,MLV_Font* font);
int display_dept_of_the_quadtree(BodyNode* universe,MLV_Font* font);


#endif
