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




void menu(Galaxy* galaxy){

	int x,y;
	//MLV_Mouse_button* state_mouse;
	char text1_1[50]="The quadtree";

	char text2_1[50]="The debug quadtree ";

	int height_value = WINDOW_HEIGHT*0.07;
	int width_value_1 = WINDOW_WIDTH*0.35;
	int width_value_2 = WINDOW_WIDTH*0.55;

	int height_value_size = WINDOW_HEIGHT*0.20;
	int width_value_size = WINDOW_HEIGHT*0.05;

	while(1){

		MLV_get_mouse_position(&x,&y);
		//MLV_get_mouse_button_state(state_mouse);

		//MLV_Font* font = MLV_load_font( "small_font.ttf" , WINDOW_HEIGHT*0.020 );

		if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED &&
				x > height_value && x < height_value + height_value_size &&
				y > width_value_1 && y < width_value_1 + width_value_size){

			update_all_bodies(galaxy);

		}

		if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED &&
				x > height_value && x < height_value + height_value_size &&
				y > width_value_2 && y < width_value_2 + width_value_size){

			update_all_bodies_debug(galaxy);

		}

		MLV_draw_filled_rectangle(height_value,width_value_1,WINDOW_HEIGHT*0.20,WINDOW_HEIGHT*0.05,MLV_COLOR_PINK);
		MLV_draw_filled_rectangle(height_value,width_value_2,WINDOW_HEIGHT*0.20,WINDOW_HEIGHT*0.05,MLV_COLOR_PINK);

		MLV_draw_text(WINDOW_HEIGHT*0.11,WINDOW_WIDTH*0.365,text1_1,MLV_COLOR_BLUE);
		MLV_draw_text(WINDOW_HEIGHT*0.083,WINDOW_WIDTH*0.564,text2_1,MLV_COLOR_BLUE);

		//MLV_draw_text_with_font(WINDOW_HEIGHT*0.55,WINDOW_WIDTH*0.87,text2_2,font,MLV_COLOR_BLUE);

		MLV_update_window();
		//MLV_free_font(font);
		MLV_wait_milliseconds(2);
		//getchar();

	}
	return;
}



int main(int argc, char** argv)
{
	Galaxy* galaxy = galaxy_reader(argv[1]);

	if(galaxy == NULL)
	{
		printf("the universe is non existent ...\n");
		return 0;
	}

	display_window();

	menu(galaxy);

	//update_all_bodies(galaxy);

	//update_all_bodies_debug(galaxy);

	free_galaxy(galaxy);
	free_window();

	return 0;
}
