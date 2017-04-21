#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <windows.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;

int wallCollide(int x, int y, int dir, int level[20][20]);

const int RIGHT = 1;
const int LEFT = 2;
const int UP = 3;
const int DOWN = 4;

const int PACSIZE = 30;

int main()
{

	int level[20][20] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,1,
		1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,
		1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,1,
		1,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,
		1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,
		1,0,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,0,1,
		1,0,0,0,1,0,1,0,1,3,3,1,0,1,0,1,0,0,0,1,
		0,0,1,0,1,0,0,0,1,3,3,1,0,0,0,1,0,1,0,0,
		0,0,1,0,1,1,1,0,1,3,3,1,0,1,1,1,0,1,0,0,
		1,0,0,0,0,0,0,0,1,3,3,1,0,0,0,0,0,0,0,1,
		1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,1,0,1,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};



	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *dot = NULL;
	ALLEGRO_BITMAP *wall = NULL;
	ALLEGRO_BITMAP *ghostgate = NULL;
	ALLEGRO_BITMAP *pacman = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	float pacman_dx = -6, pacman_dy = 6;

	int pacman_x = 50;
	int pacman_y = 50;

	int score = 0;

	bool key[4] = { false, false, false, false };

	bool redraw = true;

	bool doexit = false;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	al_init_font_addon();

	al_init_ttf_addon();

	al_init_primitives_addon();

	display = al_create_display(800, 800);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_install_keyboard();

	timer = al_create_timer(.02);

	display = al_create_display(800, 900);

	wall = al_create_bitmap(40, 40);

	ghostgate = al_create_bitmap(80, 5);

	pacman = al_create_bitmap(30, 30);

	dot = al_create_bitmap(5, 5);

	font = al_load_ttf_font("score.ttf", 96, 0);

	al_set_target_bitmap(ghostgate);
	al_clear_to_color(al_map_rgb(255, 182, 193));

	al_set_target_bitmap(dot);
	al_clear_to_color(al_map_rgb(255,255,255));

	al_set_target_bitmap(pacman);
	al_clear_to_color(al_map_rgb(255, 255, 0));

	al_set_target_bitmap(wall);
	al_clear_to_color(al_map_rgb(0, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (!doexit) {

		cout << "(" << pacman_x << ", " << pacman_y << ")" << endl;

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if (key[0] && wallCollide(pacman_x, pacman_y, LEFT, level) == 0) {
				pacman_x -= 4.0;
			}

			if (key[1] && wallCollide(pacman_x, pacman_y, RIGHT, level) == 0) {
				pacman_x += 4.0;
			}

			if (key[2] && wallCollide(pacman_x, pacman_y, UP, level) == 0) {
				pacman_y -= 4.0;
			}

			if (key[3] && wallCollide(pacman_x, pacman_y, DOWN, level) == 0) {
				pacman_y += 4.0;
			}

			if (level[(pacman_y + 15) / 40][(pacman_x + 15) / 40] == 0) {
				level[(pacman_y + 15) / 40][(pacman_x + 15) / 40] = 2;
				score++;
			}

			redraw = true;
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
				key[0] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[1] = true;
				break;

			case ALLEGRO_KEY_UP:
				key[2] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[3] = true;
				break;

			}//SWITCH TO KEYCODE
		}//KEY_DOWN

		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
				key[0] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[1] = false;
				break;

			case ALLEGRO_KEY_UP:
				key[2] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[3] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			}//SWITCH TO KEYCODE
		}//KEY_UP

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(ghostgate, 360, 321, 0);

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++) {
					if (level[i][j] == 1)
						al_draw_bitmap(wall, j * 40, i * 40, 0);
					else if (level[i][j] == 0)
						al_draw_bitmap(dot, j * 40 + 20, i * 40 + 20, 0);
				}

			al_draw_bitmap(pacman, pacman_x, pacman_y, 0);

			al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 810, 0, "Score = %i", score);

			al_flip_display();

		}//end render


	}//end loop
	al_destroy_display(display);

	return 0;
}//end main

int wallCollide(int x, int y, int dir, int level[20][20]) {

	int new_x1, new_x2, new_x3, new_y1, new_y2, new_y3;

	if (dir == RIGHT) { 		// Moving Right
								// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		new_x1 = x + 4 + PACSIZE;
		new_x2 = x + 4 + PACSIZE;
		new_x3 = x + 4 + PACSIZE;
		// Check at three point along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE / 2;
		new_y3 = y + PACSIZE;

		if (level[new_y1 / 40][new_x1 / 40] == 1 || level[new_y2 / 40][new_x2 / 40] == 1 || level[new_y3 / 40][new_x3 / 40] == 1)
			return 1;
	}

	else if (dir == LEFT) { 		// Moving Left
								// Check along the far left side of the sprite, minus 3 (the amount we’re moving)
		new_x1 = x - 7;
		new_x2 = x - 7;
		new_x3 = x - 7;
		// Check at three point along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE / 2;
		new_y3 = y + PACSIZE;

		if (level[new_y1 / 40][new_x1 / 40] == 1 || level[new_y2 / 40][new_x2 / 40] == 1 || level[new_y3 / 40][new_x3 / 40] == 1)
			return 1;
	}

	else if (dir == DOWN) { 		// Moving Down
									// Check along the far down side of the sprite, minus 3 (the amount we’re moving)
		new_x1 = x;
		new_x2 = x + PACSIZE;
		new_x3 = x + PACSIZE / 2;
		// Check at three point along that edge
		new_y1 = y + 4 + PACSIZE;
		new_y2 = y + PACSIZE + 4;
		new_y3 = y + PACSIZE + 4;

		if (level[new_y1 / 40][new_x1 / 40] == 1 || level[new_y2 / 40][new_x2 / 40] == 1 || level[new_y3 / 40][new_x3 / 40] == 1)
			return 1;
	}
	

	else if (dir == UP) { 		// Moving Down
									// Check along the far down side of the sprite, minus 3 (the amount we’re moving)
		new_x1 = x;
		new_x2 = x + PACSIZE;
		new_x3 = x + PACSIZE / 2;
		// Check at three point along that edge
		new_y1 = y - 6;
		new_y2 = y - 6;
		new_y3 = y - 6;

		if (level[new_y1 / 40][new_x1 / 40] == 1 || level[new_y2 / 40][new_x2 / 40] == 1 || level[new_y3 / 40][new_x3 / 40] == 1)
			return 1;
	}

	return 0;
}