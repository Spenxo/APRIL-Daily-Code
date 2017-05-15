#pragma once
#include "ghost.h"
#include <allegro5\allegro.h>
#include <allegro5/allegro_primitives.h>
#include<iostream>
using namespace std;
//#include "Source.cpp"
#include"globals.h"


void GHOST::Ghost() {
	int hitwall = 0;
	int xpos = 0;
	int ypos = 0;
	char color = 's';
	int direction = 0;
	bool dead = false;
	int speed = 0;

}
void GHOST::initGhost(int x, int y, char c, int dir, int Gspeed) {
	xpos = x;
	ypos = y;
	color = c;
	direction = dir;
	speed = Gspeed;
	dead = false;
}
bool GHOST::isdead() {
	return dead;
}
void GHOST::drawGhost(char c) {
		if (c == 'r') {
			al_draw_filled_rectangle(xpos, ypos, xpos + PACSIZE, ypos + PACSIZE, al_map_rgb(255, 0, 0));
		}
		if (c == 'b') {
			al_draw_filled_rectangle(xpos, ypos, xpos + PACSIZE, ypos + PACSIZE, al_map_rgb(0, 0, 255));
		}
		if (c == 'g') {
			al_draw_filled_rectangle(xpos, ypos, xpos + PACSIZE, ypos + PACSIZE, al_map_rgb(0, 235, 0));
		}
		if (c == 'p') {
			al_draw_filled_rectangle(xpos, ypos, xpos + PACSIZE, ypos + PACSIZE, al_map_rgb(255, 282, 193));
		}
}
void GHOST::printinfo() {}
//chase function. x and y are pacman's position.


int GHOST::chase(int x, int y, int field[20][20]) {
	cout << "starting chase function" << endl;
	cout << "direction is " << direction << endl;
	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/



	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, field) && y < ypos)
		while (!wallCollide(xpos, ypos, UP, field)) {
			 cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 4;
			return 1;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xpos, ypos, DOWN, field) && y > ypos)
		while (!wallCollide(xpos, ypos, 4, field)) {
			  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 4;
			return 1;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			xpos -= 4;
			return 1;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xpos, ypos, LEFT, field) && x < xpos)
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 4;
			return 1;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x > xpos)
		while (!wallCollide(xpos, ypos, 3, field)) {
			 cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 6;
			return 1;
		}
	if (direction == UP)//up
		while (!wallCollide(xpos, ypos, 2, field)) {
			ypos -= UP;
			return 1;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, field) && y < ypos)
		while (!wallCollide(xpos, ypos, 2, field)) {
			   cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 5;
			return 1;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, field) && y > ypos)
		while (!wallCollide(xpos, ypos, DOWN, field)) {
			  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 4;
			return 1;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xpos, ypos, RIGHT, field)) {
			xpos += 6;
			return 1;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, field) && x < xpos)
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			 cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 2;
			return 1;
		}

	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x > xpos)
		while (!wallCollide(xpos, ypos, RIGHT, field)) {
			   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 5;
			return 1;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xpos, ypos, DOWN, field)) {
			ypos += 5;
			return 1;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < ypos) && !wallCollide(xpos, ypos, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return 1;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > ypos) && !wallCollide(xpos, ypos, DOWN, field)) {
		direction = DOWN;
		   cout << "direction is down" << endl;
		return 1;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xpos) && !wallCollide(xpos, ypos, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return 1;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xpos) && !wallCollide(xpos, ypos, LEFT, field)) {
		direction = LEFT;
		 cout << "direction is left" << endl;
		return 1;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xpos, ypos, UP, field)) {
		 cout << "direction is up" << endl;
		direction = UP;
		return 1;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xpos, ypos, DOWN, field)) {
		direction = DOWN;
		cout << "direction is down" << endl;
		return 1;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xpos, ypos, RIGHT, field)) {
		direction = RIGHT;
		  cout << "direction is right" << endl;
		return 1;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xpos, ypos, LEFT, field)) {
		direction = LEFT;
		 cout << "direction is left" << endl;
		return 1;

	}
	else
		return 0;
}

int GHOST::chase2(int x, int y, int field[20][20]) {
	cout << "starting chase function" << endl;
	cout << "direction is " << direction << endl;
	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/



	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, field) && y < ypos)
		while (!wallCollide(xpos, ypos, UP, field)) {
			cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 6;
			return 1;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xpos, ypos, DOWN, field) && y > ypos)
		while (!wallCollide(xpos, ypos, 4, field)) {
			cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 5;
			return 1;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			xpos -= 4;
			return 1;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xpos, ypos, LEFT, field) && x < xpos)
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 5;
			return 1;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x > xpos)
		while (!wallCollide(xpos, ypos, 3, field)) {
			cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 4;
			return 1;
		}
	if (direction == UP)//up
		while (!wallCollide(xpos, ypos, 2, field)) {
			ypos -= UP;
			return 1;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, field) && y < ypos)
		while (!wallCollide(xpos, ypos, 2, field)) {
			cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 5;
			return 1;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, field) && y > ypos)
		while (!wallCollide(xpos, ypos, DOWN, field)) {
			cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 5;
			return 1;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xpos, ypos, RIGHT, field)) {
			xpos += 4;
			return 1;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, field) && x < xpos)
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 4;
			return 1;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x > xpos)
		while (!wallCollide(xpos, ypos, RIGHT, field)) {
			cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 7;
			return 1;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xpos, ypos, DOWN, field)) {
			ypos += 6;
			return 1;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < ypos) && !wallCollide(xpos, ypos, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return 1;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > ypos) && !wallCollide(xpos, ypos, DOWN, field)) {
		direction = DOWN;
		cout << "direction is down" << endl;
		return 1;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xpos) && !wallCollide(xpos, ypos, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return 1;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xpos) && !wallCollide(xpos, ypos, LEFT, field)) {
		direction = LEFT;
		cout << "direction is left" << endl;
		return 1;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xpos, ypos, UP, field)) {
		cout << "direction is up" << endl;
		direction = UP;
		return 1;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xpos, ypos, DOWN, field)) {
		direction = DOWN;
		cout << "direction is down" << endl;
		return 1;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xpos, ypos, RIGHT, field)) {
		direction = RIGHT;
		cout << "direction is right" << endl;
		return 1;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xpos, ypos, LEFT, field)) {
		direction = LEFT;
		cout << "direction is left" << endl;
		return 1;

	}
	else
		return 0;
}

int GHOST::chase3(int x, int y, int field[20][20]) {
	cout << "starting chase function" << endl;
	cout << "direction is " << direction << endl;
	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/



	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, field) && y < ypos)
		while (!wallCollide(xpos, ypos, UP, field)) {
			cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 6;
			return 1;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xpos, ypos, DOWN, field) && y > ypos)
		while (!wallCollide(xpos, ypos, 4, field)) {
			cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 5;
			return 1;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			xpos -= 5;
			return 1;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xpos, ypos, LEFT, field) && x < xpos)
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 5;
			return 1;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x > xpos)
		while (!wallCollide(xpos, ypos, 3, field)) {
			cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 4;
			return 1;
		}
	if (direction == UP)//up
		while (!wallCollide(xpos, ypos, 2, field)) {
			ypos -= UP;
			return 1;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, field) && y < ypos)
		while (!wallCollide(xpos, ypos, 2, field)) {
			cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 6;
			return 1;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, field) && y > ypos)
		while (!wallCollide(xpos, ypos, DOWN, field)) {
			cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 5;
			return 1;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xpos, ypos, RIGHT, field)) {
			xpos += 5;
			return 1;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, field) && x < xpos)
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 5;
			return 1;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x > xpos)
		while (!wallCollide(xpos, ypos, RIGHT, field)) {
			cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 4;
			return 1;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xpos, ypos, DOWN, field)) {
			ypos += 6;
			return 1;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < ypos) && !wallCollide(xpos, ypos, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return 1;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > ypos) && !wallCollide(xpos, ypos, DOWN, field)) {
		direction = DOWN;
		cout << "direction is down" << endl;
		return 1;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xpos) && !wallCollide(xpos, ypos, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return 1;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xpos) && !wallCollide(xpos, ypos, LEFT, field)) {
		direction = LEFT;
		cout << "direction is left" << endl;
		return 1;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xpos, ypos, UP, field)) {
		cout << "direction is up" << endl;
		direction = UP;
		return 1;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xpos, ypos, DOWN, field)) {
		direction = DOWN;
		cout << "direction is down" << endl;
		return 1;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xpos, ypos, RIGHT, field)) {
		direction = RIGHT;
		cout << "direction is right" << endl;
		return 1;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xpos, ypos, LEFT, field)) {
		direction = LEFT;
		cout << "direction is left" << endl;
		return 1;

	}
	else
		return 0;
}

bool GHOST::getPacman(int pacman_x, int pacman_y) {
	if ((xpos + 30 > pacman_x && xpos < pacman_x + 30) &&
		(ypos + 30 > pacman_y && ypos < pacman_y + 30)){
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		//al_flip_display();
		return 1;
	}
	else 
		return 0;
}

int GHOST::wallCollide(int x, int y, int dir, int level[20][20]) {

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
