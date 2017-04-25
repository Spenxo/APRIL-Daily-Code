#include <iostream>
using namespace std;

bool Horoscope(int bm);



int main() {

	do {
		int bm;

		cout << "Give me a number from 1-12 corresponding to your birth month." << endl;
		cin >> bm;
		if (Horoscope(bm) == true) {
			Horoscope(bm);
		}
		else
			cout << "Go away" << endl;
	} while (1);
}

bool Horoscope(int bm) {
	if (bm == 4) {
		cout << "You were born in April. You're a fool :o" << endl;
		return true;
	}
}