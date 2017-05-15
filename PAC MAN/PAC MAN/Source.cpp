#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <windows.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "ghost.h"
#include "globals.h"
using namespace std;

int wallCollide(int x, int y, int dir, int level[20][20]);

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};



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
	ALLEGRO_BITMAP *paclife1 = NULL;
	ALLEGRO_BITMAP *paclife2 = NULL;
	ALLEGRO_BITMAP *paclife3 = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance = NULL;
	ALLEGRO_BITMAP *dot = NULL;
	ALLEGRO_BITMAP *wall = NULL;
	ALLEGRO_BITMAP *ghostgate = NULL;
	ALLEGRO_BITMAP *pacman = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *WalkHorizontal;
	ALLEGRO_BITMAP *WalkVertical;
	

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	al_init_font_addon();

	al_init_ttf_addon();

	al_install_audio();
	al_init_acodec_addon();

	al_init_image_addon();

	al_init_primitives_addon();

	
	WalkHorizontal = al_load_bitmap("pacmanboyyohorizontal.png");
	
	al_convert_mask_to_alpha(WalkHorizontal, al_map_rgb(255, 255, 255));
	
	WalkVertical = al_load_bitmap("pacmanboyyovertical.png");

	
	al_convert_mask_to_alpha(WalkVertical, al_map_rgb(255, 255, 255));

	float pacman_dx = -20, pacman_dy = 20;
	al_rest(2);
	int pacman_x = 47;
	int pacman_y = 47;

	int rx = 405;
	int gx = 405;
	int px = 366;
	int bx = 405;
	int ry = 378;
	int gy = 430;
	int py = 430;
	int by = 334;


	int width = 800;
	int height = 900;

	int x = width / 2;
	int y = height / 2;

	int score = 0;

	int lives = 3;

	bool key[4] = { false, false, false, false };

	bool redraw = true;

	bool doexit = false;

	//sprite variables////////////////////////////////////////////
	const int maxFrame = 2;     //how many pictures in your bitmap
	int curFrame = 0; //starting point
	int frameCount = 0; //what number frame you're on
	int frameDelay = 5; //speed up or slow down feet 
	int frameWidth = 30;
	int frameHeight = 30;
	int dir = 0;
	///////////////////////////////////////////////////////////////


	display = al_create_display(width, height);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_install_keyboard();

	timer = al_create_timer(.03);

	display = al_create_display(800, 900);

	wall = al_create_bitmap(WALLSIZE, WALLSIZE);

	ghostgate = al_create_bitmap(80, 2);

	sample = al_load_sample("BGmusic.wav");
	al_reserve_samples(2);

	pacman = al_create_bitmap(PACSIZE, PACSIZE);

	dot = al_create_bitmap(20, 20);

	font = al_load_ttf_font("score.ttf", 96, 0);

	al_set_target_bitmap(ghostgate);
	al_clear_to_color(al_map_rgb(255, 182, 193));

	al_set_target_bitmap(dot);
	al_clear_to_color(al_map_rgb(255, 255, 255));

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

instance = al_create_sample_instance(sample);
al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);

al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());

al_flip_display();

al_start_timer(timer);

GHOST redghost;
redghost.initGhost(rx, ry, 'r', RIGHT, 500);

GHOST pinkghost;
pinkghost.initGhost(px, py, 'p', RIGHT, 500);

GHOST greenghost;
greenghost.initGhost(gx, gy, 'g', RIGHT, 500);

GHOST blueghost;
blueghost.initGhost(bx, by, 'b', RIGHT, 500);

al_clear_to_color(al_map_rgb(0, 0, 0));
al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTRE, "NAMCAP");
al_flip_display();
al_rest(.2);


al_clear_to_color(al_map_rgb(33, 244, 25));
al_draw_text(font, al_map_rgb(130, 170, 199), 400, 400, ALLEGRO_ALIGN_CENTRE, "(PACMAN BACKWARDS)");
al_flip_display();
al_rest(.3);

while (!doexit) {

	cout << "(" << pacman_x << ", " << pacman_y << ")" << endl;

	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);

	if (ev.type == ALLEGRO_EVENT_TIMER) {

		if (key[0] && wallCollide(pacman_x, pacman_y, LEFT, level) == 0) {
			pacman_x -= 8.0;
			dir = LEFT;
		}

		if (key[1] && wallCollide(pacman_x, pacman_y, RIGHT, level) == 0) {
			pacman_x += 8.0;
			dir = RIGHT;
		}

		if (key[2] && wallCollide(pacman_x, pacman_y, UP, level) == 0) {
			pacman_y -= 8.0;
			dir = UP;
		}

		if (key[3] && wallCollide(pacman_x, pacman_y, DOWN, level) == 0) {
			pacman_y += 8.0;
			dir = DOWN;
		}

		if (level[(pacman_y + 15) / WALLSIZE][(pacman_x + 15) / WALLSIZE] == 0) {
			level[(pacman_y + 15) / WALLSIZE][(pacman_x + 15) / WALLSIZE] = 2;
			score++;
		}

		redghost.chase3(pacman_x, pacman_y, level);
		greenghost.chase(pacman_x, pacman_y, level);
		blueghost.chase3(pacman_x, pacman_y, level);
		pinkghost.chase2(pacman_x, pacman_y, level);

		if (lives == 0) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTRE, "YOU LOSE");
			al_flip_display();
			al_rest(1);
			return 0;
		}

		if (redghost.getPacman(pacman_x, pacman_y) == 1) {
			pacman_x = 47;
			pacman_y = 47;
			lives--;
		}

		if (greenghost.getPacman(pacman_x, pacman_y) == 1) {
			pacman_x = 47;
			pacman_y = 47;
			lives--;
		}
		if (blueghost.getPacman(pacman_x, pacman_y)) {
			pacman_x = 47;
			pacman_y = 47;
			lives--;
		}
		if (pinkghost.getPacman(pacman_x, pacman_y)) {
			pacman_x = 47;
			pacman_y = 47;
			lives--;
		}


			if (score == 206) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTRE, "YOU WIN");
				al_flip_display();
				al_rest(2);
				return 0;
			}

			//left warp zone
			if (pacman_x == -33 && pacman_y >= 367 && pacman_y <= 403) {
				pacman_x = 802;
				pacman_y = 363;
			}
			//right warp zone
			if (pacman_x >= 803 && pacman_x <= 850 && pacman_y >= 363 && pacman_y <= 367) {
				pacman_x = -33;
				pacman_y = 367;
			}

			//move sprite////////////////////////////////////////////////
			if (++frameCount >= frameDelay)
			{
				if (++curFrame >= maxFrame) //if you've walked off the end, go back to the beginning
					curFrame = 0;

				frameCount = 0; //reset frame timer
			}

			if (x <= 0 - frameWidth)
				x = width;
			///////////////////////////////////////////////////////////////


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
			cout << "starting render section" << endl;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			paclife1 = al_load_bitmap("paclife.jpg");
			paclife2 = al_load_bitmap("paclife.jpg");
			paclife3 = al_load_bitmap("paclife.jpg");

			if (lives != 2 && lives != 1 && lives != 0) {
				al_draw_bitmap(paclife3, 5, 865, 0);
			}
			if (lives != 1 && lives !=0) {
				al_draw_bitmap(paclife2, 35, 865, 0);
			}
			if (lives != 0) {
				al_draw_bitmap(paclife1, 65, 865, 0);
			}
			cout << "drawing ghostgate" << endl;
			al_draw_bitmap(ghostgate, 360, 321, 0);

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++) {
					if (level[i][j] == 1)
						al_draw_bitmap(wall, j * WALLSIZE, i * WALLSIZE, 0);
					else if (level[i][j] == 0)
						al_draw_bitmap(dot, j *WALLSIZE + 10, i *WALLSIZE + 10, 0);
				}
			cout << "draw ghost" << endl;
			if (redghost.isdead() == 0) {
				redghost.drawGhost('r');
			}
			if (blueghost.isdead() == 0) {
				blueghost.drawGhost('b');
			}
			if (pinkghost.isdead() == 0) {
				pinkghost.drawGhost('p');
			}
			if (greenghost.isdead() == 0) {
				greenghost.drawGhost('g');
			}
			cout << "draw pacman" << endl;
			//al_draw_bitmap(pacman, pacman_x, pacman_y, 0);

			al_draw_textf(font, al_map_rgb(240, 255, 255), 5, 790, 0, "Score = %i", score);
			cout << "darw bitmap region" << endl;

			if (WalkHorizontal == NULL)
				cout << "something snarky" << endl;
			
			//////////////draw bitmap REGION///////////////////////////////////
			if (dir == LEFT)
			al_draw_bitmap_region(WalkHorizontal, curFrame * frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 1);
			else if (dir == RIGHT)	
				al_draw_bitmap_region(WalkHorizontal, curFrame * frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 0);
			else if (dir ==UP)
			al_draw_bitmap_region(WalkVertical, curFrame * frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 3);
			else if (dir==DOWN)
				al_draw_bitmap_region(WalkVertical, curFrame * frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 4);
			//////////////////////////////////////////////////////////////////
			cout << "end render" << endl;
			al_play_sample_instance(instance);

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
		new_x1 = x + 8 + PACSIZE;
		new_x2 = x + 8 + PACSIZE;
		new_x3 = x + 8 + PACSIZE;
		// Check at three point along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE / 2;
		new_y3 = y + PACSIZE;

		if (level[new_y1 / WALLSIZE][new_x1 / WALLSIZE] == 1 || level[new_y2 / WALLSIZE][new_x2 / WALLSIZE] == 1 || level[new_y3 / WALLSIZE][new_x3 / WALLSIZE] == 1)
			return 1;
	}

	else if (dir == LEFT) { 		// Moving Left
								// Check along the far left side of the sprite, minus 3 (the amount we’re moving)
		new_x1 = x - 8;
		new_x2 = x - 8;
		new_x3 = x - 8;
		// Check at three point along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE / 2;
		new_y3 = y + PACSIZE;

		if (level[new_y1 / WALLSIZE][new_x1 / WALLSIZE] == 1 || level[new_y2 / WALLSIZE][new_x2 / WALLSIZE] == 1 || level[new_y3 / WALLSIZE][new_x3 / WALLSIZE] == 1)
			return 1;
	}

	else if (dir == DOWN) { 		// Moving Down
									// Check along the far down side of the sprite, minus 3 (the amount we’re moving)
		new_x1 = x;
		new_x2 = x + PACSIZE;
		new_x3 = x + PACSIZE / 2;
		// Check at three point along that edge
		new_y1 = y + 8 + PACSIZE;
		new_y2 = y + 8 + PACSIZE;
		new_y3 = y + 8 + PACSIZE;

		if (level[new_y1 / WALLSIZE][new_x1 / WALLSIZE] == 1 || level[new_y2 / WALLSIZE][new_x2 / WALLSIZE] == 1 || level[new_y3 / WALLSIZE][new_x3 / WALLSIZE] == 1)
			return 1;
	}


	else if (dir == UP) { 		// Moving Down
									// Check along the far down side of the sprite, minus 3 (the amount we’re moving)
		new_x1 = x;
		new_x2 = x + PACSIZE;
		new_x3 = x + PACSIZE / 2;
		// Check at three point along that edge
		new_y1 = y - 8;
		new_y2 = y - 8;
		new_y3 = y - 8;

		if (level[new_y1 / WALLSIZE][new_x1 / WALLSIZE] == 1 || level[new_y2 / WALLSIZE][new_x2 / WALLSIZE] == 1 || level[new_y3 / WALLSIZE][new_x3 / WALLSIZE] == 1)
			return 1;
	}

	return 0;
}
