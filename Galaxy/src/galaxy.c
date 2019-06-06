#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/physics.h"
#include "../headers/graphic.h"
#include "../headers/galaxy.h"
#include "../headers/galaxy_manager.h"

/*void menu(){
	char input;
	while (1) {
	    printf("\n\n\nEnter a command : ");
        scanf(" %c",&input);
	    switch (input) {
		    case 'h':
		        printf("+-----------------------+\n");
		        printf("|         Menu          |\n");
		        printf("+-----------------------+\n");
		       	printf("n   - normal mode\n");
				printf("s   - stats mode\n");
				printf("c   - color mode\n");
				printf("d   - division mode\n");
				printf("f   - full mode\n");
		        printf("q   - quit\n");
		        break;
			case 'n':
				break:
			case 's':
			case 'c':
			case 'd':
			case 'f':
		    default:
		        printf("Unknown selection. Use 'h' for help.\n");
		    }
		    get_input(&ch, &arg);
	}

}*/


int main(int argc, char** argv)
{
	Galaxy* galaxy = galaxy_reader(argv[1]);

	if(galaxy == NULL)
	{
		printf("the universe is non existent ...\n");
		return 0;
	}

	//display_window();

	//update_all_bodies(galaxy);

	update_all_bodies_debug(galaxy);

	free_galaxy(galaxy);
	free_window();

	return 0;
}
