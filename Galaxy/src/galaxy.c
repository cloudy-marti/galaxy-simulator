#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include <time.h>

#include "../headers/physics.h"
#include "../headers/graphic.h"
#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"

int main(int argc, char** argv)
{
	Galaxy* galaxy = galaxy_reader(argv[1]);

	if(galaxy == NULL)
	{
		printf("the universe is non existent ...\n");
		return 0;
	}

	srand(time(NULL));

	display_window();

	menu(galaxy);

	//update_all_bodies(galaxy);

	free_galaxy(galaxy);
	free_window();

	return 0;
}