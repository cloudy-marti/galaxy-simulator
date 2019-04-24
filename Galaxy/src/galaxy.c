#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/physics.h"
#include "../headers/graphic.h"
#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"
#include "../headers/visualtree.h"
#include "../headers/quadtree.h"

#define DEBUG 1

int main(int argc, char** argv)
{



	if (DEBUG == 1)
	{
		BodyNode* universe = fake_uniserse_debug_one_body();
		write_tree(universe);

	}
	else{



		Galaxy* galaxy = galaxy_reader(argv[1]);


		if(galaxy == NULL)
		{
			printf("file not read ...\n");
			return 0;
		}

	}

	/*update_all_bodies(galaxy);*/




	/*free_galaxy(galaxy);
	free_window();*/

	return 0;
}
