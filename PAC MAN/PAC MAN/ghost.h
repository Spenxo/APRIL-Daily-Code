#pragma once
class GHOST {
public:
	void Ghost();
	void initGhost(int x, int y, char c, int dir, int Gspeed);
	bool isdead();
	void drawGhost(char c);
	void printinfo();
	int chase(int x, int y, int field[20][20]);
	int chase2(int x, int y, int field[20][20]);
	int chase3(int x, int y, int field[20][20]);
	bool getPacman(int pacman_x, int pacman_y);

private:
	int hitwall;
	int xpos;
	int ypos;
	char color;
	int direction;
	bool dead;
	int speed;
	int wallCollide(int x, int y, int dir, int level[20][20]);
};
