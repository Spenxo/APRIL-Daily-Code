#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <ctime>
#include <vector>
#include <stdio.h>

using namespace std;


int main() {

	vector<int>nodes;
	vector<int>::const_iterator iter;

	al_init();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *snake = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance1 = NULL;
	ALLEGRO_FONT*font = al_create_builtin_font();

	double CLOCK = .07;
	int score = 0;

	int SNAKESIZE = 40;

	//int goal_x = rand() % 20;
	//int goal_y = rand() % 20;

	int goal_x = 5;
	int goal_y = 5;

	snake = al_create_bitmap(SNAKESIZE, SNAKESIZE);

	int head_x = 4;
	int head_y = 5;

	bool gotGoal = false;

	bool key[4] = { false, false, false, false };

	bool redraw = true;

	bool doexit = false;

	int SnakeLength = 0;

	al_reserve_samples(2);
	sample = al_load_sample("music.wav");
	al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

	al_set_target_bitmap(snake);

	al_clear_to_color(al_map_rgb(255, 255, 255));

	timer = al_create_timer(CLOCK);
	display = al_create_display(800, 1000);

	int grid[20][20];

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			grid[i][j] = 0;

	grid[goal_x][goal_y] = 2;

	srand(time(NULL));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_reserve_samples(10);

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	//al_play_sample_instance(instance1);

	while (true) {
		int color1 = rand() % 158;
		int color2 = rand() % 21;
		int color3 = rand() % 90;
		int color4 = rand() % 255;
		int color5 = rand() % 255;
		int color6 = rand() % 255;
		int color7 = rand() % 255;
		int color8 = rand() % 255;
		int color9 = rand() % 255;

		//cout << "shoe" << endl;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		/*for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++)
				cout << grid[i][j];
			cout << endl;
		}*/

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++) {
					if (grid[i][j] == 1) {
						grid[i][j] = 0;
					}
				}
			for (int i = 0; i < SnakeLength; i = i + 2) {
				grid[nodes[i]][nodes[i + 1]] = 1;
			}



			if (gotGoal == true) {
				grid[goal_x][goal_y] = 0;
				goal_x = rand() % 20;
				goal_y = rand() % 20;
				grid[goal_x][goal_y] = 2;
				score++;
				gotGoal = false;
			}

			if (key[0] && head_y > -1) {
				head_y -= 1;
			}
			if (key[1] && head_y < 21) {
				head_y += 1;
			}
			if (key[2] && head_x > -1) {
				head_x -= 1;
			}
			if (key[3] && head_x < 21) {
				head_x += 1;
			}

			if (grid[goal_x] == grid[head_x] && grid[goal_y] == grid[head_y]) {
				gotGoal = true;
				SnakeLength += 2;
			}

			if (head_x >= 0 &&
				head_y >= 0 &&
				head_x < 20 &&
				head_y < 20)
				grid[head_x][head_y] = 1;

			nodes.insert(nodes.begin(), head_y);
			nodes.insert(nodes.begin(), head_x);

			if (head_x < 0 || head_y < 0) {
				cout << "MATRIX ERROR" << endl;
			}

			//if (SnakeLength > 2) {
				for (iter = nodes.begin() + 2; iter < nodes.end(); iter += 2) {
					if ((head_x == *iter && head_y == *(iter + 1))) {
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font, al_map_rgb(250, 100, 0), 300, 300, NULL, "Snake is Dead!");
						al_flip_display();
						al_rest(2);

						return 0;
					}
				}
			//}

			nodes.erase(nodes.begin() + SnakeLength, nodes.end());

			redraw = true;

		}// end timer section

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[0] = true;
				key[1] = false;
				key[2] = false;
				key[3] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[0] = false;
				key[1] = true;
				key[2] = false;
				key[3] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[0] = false;
				key[1] = false;
				key[2] = true;
				key[3] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[0] = false;
				key[1] = false;
				key[2] = false;
				key[3] = true;
				break;

			case ALLEGRO_KEY_ESCAPE:
				return 0;
				break;

			}


		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				break;
			case ALLEGRO_KEY_DOWN:
				break;
			case ALLEGRO_KEY_RIGHT:
				break;
			case ALLEGRO_KEY_LEFT:
				break;
			case ALLEGRO_KEY_ESCAPE:
				return 0;
				break;
			}
		}


		/////////////////////le rendar section////////////////////////////////////////////////////////////////
		cout << "redraw is " << redraw << " , " << "event queue is " << al_is_event_queue_empty(event_queue) << endl;
		
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			cout << "flag1" << endl;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (gotGoal == false) {
				grid[goal_x][goal_y] = 2;
			}
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++) {
					
					if (grid[i][j] == 2) {
						al_draw_filled_rectangle(i*SNAKESIZE, j*SNAKESIZE, i*SNAKESIZE + SNAKESIZE, j*SNAKESIZE + SNAKESIZE, al_map_rgb(0, 0, 0));
					}

					if (grid[i][j] == 1) {
						al_draw_filled_rectangle(i*SNAKESIZE, j*SNAKESIZE, i*SNAKESIZE + SNAKESIZE, j*SNAKESIZE + SNAKESIZE, al_map_rgb(color3, color1, color2));
					}
					if (grid[i][j] == 0) {
						al_draw_filled_rectangle(i*SNAKESIZE, j*SNAKESIZE, i*SNAKESIZE + SNAKESIZE, j*SNAKESIZE + SNAKESIZE, al_map_rgb(150, 10, 103));
					}
					
				}

			if (gotGoal == true)
				grid[goal_x][goal_y] = 0;

			//al_draw_bitmap(snake, 400, 200, 0);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 50, 800, 0, "Score:%d", score);
			al_flip_display();


		}//render section

	}//game loop

	al_destroy_sample_instance(instance1);
	al_destroy_sample(sample);
	al_destroy_bitmap(snake);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;

}//main
