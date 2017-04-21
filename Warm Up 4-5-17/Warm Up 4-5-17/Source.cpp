#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;


	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	al_init_image_addon();

	ALLEGRO_BITMAP *icon = al_load_bitmap("icon.jpg");

	if (icon == NULL)
		printf("burrrrp");

	display = al_create_display(640, 480);

	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_set_window_title(display, "Butt");

	al_set_display_icon(display, icon);

	al_flip_display();

	al_rest(10.0);

	al_destroy_display(display);

	return 0;
}