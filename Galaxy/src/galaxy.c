#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/physics.h"
#include "../headers/graphic.h"
#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"

int main(int argc, char** argv)
{
	BodyNode* galaxy = galaxy_reader(argv[1]);

	if(galaxy == NULL)
	{
		printf("the universe is non existent ...\n");
		return 0;
	}

	update_all_bodies(galaxy);

	free_quadtree(galaxy);
	free_window();

	return 0;
}