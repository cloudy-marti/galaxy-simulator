#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/physics.h"
#include "../headers/graphic.h"
#include "../headers/galaxy.h"

int main(int argc, char** argv)
{
	Galaxy* galaxy = galaxy_reader(argv[1]);

	if(galaxy == NULL)
	{
		printf("file not read ...\n");
		return 0;
	}

	update_all_bodies(galaxy);

	free_galaxy(galaxy);
	free_window();

	return 0;
}