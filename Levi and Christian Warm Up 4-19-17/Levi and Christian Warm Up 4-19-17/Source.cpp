#include <iostream>

#include <allegro5/allegro.h>

#include <math.h>

using namespace std;

const float FPS = 60;

const int SCREEN_W = 640;

const int SCREEN_H = 480;

const int ship_SIZE = 32;

enum MYKEYS {

	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE

};

int main()

{

	ALLEGRO_DISPLAY *display = NULL;

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	ALLEGRO_TIMER *timer = NULL;

	ALLEGRO_BITMAP *ship = NULL;

	ALLEGRO_BITMAP *beam = NULL;

	ALLEGRO_BITMAP *beam2 = NULL;

	float ship_x = SCREEN_W / 2.0 - ship_SIZE / 2.0;

	float ship_y = SCREEN_H / 2.0 - ship_SIZE / 2.0;

	bool key[5] = { false, false, false, false, false };

	bool redraw = true;

	bool doexit = false;

	double beam2_x = 0;

	double beam2_y = 0;

	double beam_x = 0;

	double beam_y = 0;

	int t = 0; //parameter for parametric equations

	bool shootBeam = false;

	bool shootBeam2 = false;

	al_init();

	al_install_keyboard();

	timer = al_create_timer(1.0 / FPS);

	display = al_create_display(SCREEN_W, SCREEN_H);

	//create ship

	ship = al_create_bitmap(ship_SIZE, ship_SIZE);

	al_set_target_bitmap(ship);

	al_clear_to_color(al_map_rgb(255, 0, 255));

	//create first beam object

	beam = al_create_bitmap(7, 7);

	beam2 = al_create_bitmap(4, 4);

	al_set_target_biuitmap(beam);

	al_clear_to_color(al_map_rgb(0, 160, 100));

	al_set_target_bitmap(beam2);

	al_clear_to_color(al_map_rgb(220, 167, 255));

	//set up game screen, queue, and timer to be ready to play

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (!doexit)//game loop!

	{

		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//reset beam when spacebar is first pressed!

			if (key[KEY_SPACE] && shootBeam == false) {

				t = 0; //reset time parameter

				shootBeam = true; //tell render section to draw it, and movement algorithm to freeze ship when shooting

			}

			//move beam while space is being pressed

			if (shootBeam) {
				beam_x = ship_x + t;
				////equation for beam////////////////////////////////////////////////////////////
				//LOOK! LOOK! Here's where you can change the path of the beam!

				beam_y = ship_y - 10 * sin(-9 *(beam_x += 25)) + 14;
				beam2_y = ship_y - 15 * sin(-90 * (beam2_x += 25)) + 14;

				////////////////////////////////////////////////////////////////

				t++; //increase time

				cout << "beam being fired" << endl;

			}



			//normal keyboard input movement, but only allow ship to move when not firing beam

			if (key[KEY_UP] && ship_y >= 4.0 && shootBeam == false) {

				ship_y -= 4.0;

			}

			if (key[KEY_DOWN] && ship_y <= SCREEN_H - ship_SIZE - 4.0 && shootBeam == false) {

				ship_y += 4.0;

			}

			if (key[KEY_LEFT] && ship_x >= 4.0 && shootBeam == false) {

				ship_x -= 4.0;

			}

			if (key[KEY_RIGHT] && ship_x <= SCREEN_W - ship_SIZE - 4.0 && shootBeam == false) {

				ship_x += 4.0;

			}

			//when spacebar is let go, stop drawing beam and reset position

			if (key[KEY_SPACE] == false) {

				shootBeam = false;

				shootBeam2 = false;

				beam2_x = ship_x;

				beam2_y = ship_y;

				beam_x = ship_x;

				beam_y = ship_y;

			}

			redraw = true;

		}

		//kill game if window "x" is clicked with mouse

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

			break;

		}



		//basic allegro keyboard input

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_UP:

				key[KEY_UP] = true;

				break;

			case ALLEGRO_KEY_DOWN:

				key[KEY_DOWN] = true;

				break;

			case ALLEGRO_KEY_LEFT:

				key[KEY_LEFT] = true;

				break;

			case ALLEGRO_KEY_RIGHT:

				key[KEY_RIGHT] = true;

				break;

			case ALLEGRO_KEY_SPACE:

				key[KEY_SPACE] = true;

				break;

			}

		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_UP:

				key[KEY_UP] = false;

				break;

			case ALLEGRO_KEY_DOWN:

				key[KEY_DOWN] = false;

				break;

			case ALLEGRO_KEY_LEFT:

				key[KEY_LEFT] = false;

				break;

			case ALLEGRO_KEY_RIGHT:

				key[KEY_RIGHT] = false;

				break;

			case ALLEGRO_KEY_SPACE:

				key[KEY_SPACE] = false;

				break;

			case ALLEGRO_KEY_ESCAPE:

				doexit = true;

				break;

			}

		}

		//RENDER SECTION

		if (redraw && al_is_event_queue_empty(event_queue)) {

			redraw = false;

			//only redraw when beam is NOT being fired...

			if (shootBeam == false)

				al_clear_to_color(al_map_rgb(0, 0, 0));

			//when not being fired, beam is behind ship

			al_draw_bitmap(beam, beam_x, beam_y, 0);

			al_draw_bitmap(beam2, beam_x, beam2_y, 0);

			//draw ship

			al_draw_bitmap(ship, ship_x, ship_y, 0);



			al_flip_display();

		}//end render section

	}//END GAME LOOP

	al_destroy_bitmap(ship);

	al_destroy_timer(timer);

	al_destroy_display(display);

	al_destroy_event_queue(event_queue);

	return 0;

}//end main