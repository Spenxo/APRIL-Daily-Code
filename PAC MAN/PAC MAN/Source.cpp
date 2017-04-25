#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <windows.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;

int wallCollide(int x, int rx, int px, int gx, int bx, int ry, int py, int gy, int by, int y, int dir, int level[20][20]);

const int RIGHT = 1;
const int LEFT = 2;
const int UP = 3;
const int DOWN = 4;

const int PACSIZE = 30;

class GHOST {
public:
	void Ghost();
	void initGhost(int x, int y, char c, int dir, bool dead, int Gspeed);
	bool isdead();
	void drawGhost();
	void printinfo();
	int chase(int x, int rx, int px, int gx, int bx, int ry, int py, int gy, int by, int y, int field[20][20]);
	bool getPacman(int x, int y);

private:
	int hitwall;
	int xpos;
	int ypos;
	char color;
	int direction;
	bool dead;
	int speed;
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
	ALLEGRO_BITMAP *redghost = NULL;
	ALLEGRO_BITMAP *greenghost = NULL;
	ALLEGRO_BITMAP *pinkghost = NULL;
	ALLEGRO_BITMAP *blueghost = NULL;
	ALLEGRO_BITMAP *dot = NULL;
	ALLEGRO_BITMAP *wall = NULL;
	ALLEGRO_BITMAP *ghostgate = NULL;
	ALLEGRO_BITMAP *pacman = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	float pacman_dx = -6, pacman_dy = 6;

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

	al_init_image_addon();

	al_init_primitives_addon();

	display = al_create_display(800, 900);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_install_keyboard();

	timer = al_create_timer(.02);

	display = al_create_display(1000, 1000);

	wall = al_create_bitmap(40, 40);

	ghostgate = al_create_bitmap(80, 5);

	redghost = al_create_bitmap(30, 30);
	blueghost = al_create_bitmap(30, 30);
	pinkghost = al_create_bitmap(30, 30);
	greenghost = al_create_bitmap(30, 30);

	pacman = al_create_bitmap(30, 30);

	dot = al_create_bitmap(5, 5);

	font = al_load_ttf_font("score.ttf", 96, 0);

	al_set_target_bitmap(ghostgate);
	al_clear_to_color(al_map_rgb(255, 182, 193));

	al_set_target_bitmap(dot);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(pacman);
	al_clear_to_color(al_map_rgb(255, 255, 0));

	al_set_target_bitmap(wall);
	al_clear_to_color(al_map_rgb(0, 0, 255));

	al_set_target_bitmap(pinkghost);
	al_clear_to_color(al_map_rgb(255, 105, 180));
	al_set_target_bitmap(greenghost);
	al_clear_to_color(al_map_rgb(0, 255, 0));
	al_set_target_bitmap(redghost);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_set_target_bitmap(blueghost);
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

			if (key[0] && wallCollide(pacman_x, rx, px, gx, bx, ry, py, gy, by, pacman_y, LEFT, level) == 0) {
				pacman_x -= 4.0;
			}

			if (key[1] && wallCollide(pacman_x, rx, px, gx, bx, ry, py, gy, by, pacman_y, RIGHT, level) == 0) {
				pacman_x += 4.0;
			}

			if (key[2] && wallCollide(pacman_x, rx, px, gx, bx, ry, py, gy, by, pacman_y, UP, level) == 0) {
				pacman_y -= 4.0;
			}

			if (key[3] && wallCollide(pacman_x, rx, px, gx, bx, ry, py, gy, by, pacman_y, DOWN, level) == 0) {
				pacman_y += 4.0;
			}

			if (level[(pacman_y + 15) / 40][(pacman_x + 15) / 40] == 0) {
				level[(pacman_y + 15) / 40][(pacman_x + 15) / 40] = 2;
				score++;
			}

			if (score == 206) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTRE, "YOU WIN");
				al_flip_display();
				al_rest(2);
				return 0;
			}

			if ((level[(gx + 15) / 40][(gy + 15) / 40] == 0) ||
				(level[(px + 15) / 40][(py + 15) / 40] == 0) ||
				(level[(rx + 15) / 40][(ry + 15) / 40] == 0) ||
				(level[(bx + 15) / 40][(by + 15) / 40] == 0)) {

				//chase(pacman_x, rx, px, gx, bx, ry, py, gy, by, pacman_y, level);

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

			paclife1 = al_load_bitmap("paclife.jpg");
			paclife2 = al_load_bitmap("paclife.jpg");
			paclife3 = al_load_bitmap("paclife.jpg");

			al_draw_bitmap(paclife1, 5, 865, 0);
			al_draw_bitmap(paclife2, 35, 865, 0);
			al_draw_bitmap(paclife3, 70, 865, 0);

			al_draw_bitmap(ghostgate, 360, 321, 0);

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++) {
					if (level[i][j] == 1)
						al_draw_bitmap(wall, j * 40, i * 40, 0);
					else if (level[i][j] == 0)
						al_draw_bitmap(dot, j * 40 + 20, i * 40 + 20, 0);
				}

			al_draw_bitmap(blueghost, bx, by, 0);
			al_draw_bitmap(redghost, rx, ry, 0);
			al_draw_bitmap(greenghost, gx, gy, 0);
			al_draw_bitmap(pinkghost, px, py, 0);

			al_draw_bitmap(pacman, pacman_x, pacman_y, 0);

			al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 790, 0, "Score = %i", score);

			al_flip_display();

		}//end render


	}//end loop
	al_destroy_display(display);

	return 0;
}//end main

int wallCollide(int x, int rx, int px, int gx, int bx, int ry, int py, int gy, int by, int y, int dir, int level[20][20]) {

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
		new_y1 = y + 7 + PACSIZE;
		new_y2 = y + 7 + PACSIZE;
		new_y3 = y + 7 + PACSIZE;

		if (level[new_y1 / 40][new_x1 / 40] == 1 || level[new_y2 / 40][new_x2 / 40] == 1 || level[new_y3 / 40][new_x3 / 40] == 1)
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

		if (level[new_y1 / 40][new_x1 / 40] == 1 || level[new_y2 / 40][new_x2 / 40] == 1 || level[new_y3 / 40][new_x3 / 40] == 1)
			return 1;
	}

	return 0;
}

void GHOST::Ghost() {
	int hitwall = 0;
	int xpos = 0;
	int ypos = 0;
	char color = 0;
	int direction = 0;
	bool dead = 0;
	int speed = 0;
}
void GHOST::initGhost(int x, int y, char c, int dir, bool dead, int Gspeed) {
	int xpos = x;
	int ypos = y;
	int color = c;
	int direction = dir;
	int speed = Gspeed;
}
bool GHOST::isdead() {
	return dead;
}
void GHOST::drawGhost() {

}
void GHOST::printinfo() {}
//chase function. x and y are pacman's position.
int GHOST::chase(int x, int rx, int px, int gx, int bx, int ry, int py, int gy, int by, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/

	//this is just for testing
	cout << "state is " << direction << endl;
	if (wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 1, field))
		cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 2, field))
		cout << "there's a wall above me" << endl;
	if (wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 3, field))
		cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 4, field))
		cout << "there's a wall below me" << endl;

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, UP, field) && y < ypos)
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 4;
			return 1;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, DOWN, field) && y > ypos)
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 4;
			return 1;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, LEFT, field)) {
			xpos -= 4;
			return 1;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, LEFT, field) && x < xpos)
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 4;
			return 1;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, RIGHT, field) && x > xpos)
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 4;
			return 1;
		}
	if (direction == UP)//up
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 2, field)) {
			ypos -= UP;
			return 1;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, UP, field) && y < ypos)
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 2;
			return 1;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, DOWN, field) && y > ypos)
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 2;
			return 1;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, RIGHT, field)) {
			xpos += 2;
			return 1;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, LEFT, field) && x < xpos)
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 2;
			return 1;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, RIGHT, field) && x > xpos)
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 2;
			return 1;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, DOWN, field)) {
			ypos += 2;
			return 1;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < ypos) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return 1;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > ypos) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return 1;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xpos) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return 1;
	} 

	//if pacman is left and there's no wall there, move left
	if ((x < xpos) && !wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return 1;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return 1;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return 1;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return 1;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xpos, rx, px, gx, bx, ry, py, gy, by, ypos, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return 1;

	}
	else
		return 0;
}

bool GHOST::getPacman(int x, int y) {
	return 1;
}