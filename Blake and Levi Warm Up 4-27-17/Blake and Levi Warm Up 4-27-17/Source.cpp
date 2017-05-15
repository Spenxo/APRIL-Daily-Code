#include <iostream>
using namespace std;

void Damage(double l, double  p, double  a, double  d, double m, double damage);

int main() {
	double level;
	double power;
	double attack;
	double defense;
	double modifier;
	double damage = 0;
	do {
		cout << "For your pokemon, what is the Level?" << endl;
		cin >> level;
		cout << "For your pokemon, what is the power?" << endl;
		cin >> power;
		cout << "Attack?" << endl;
		cin >> attack;
		cout << "Defense?" << endl;
		cin >> defense;
		cout << "Modifier?" << endl;
		cin >> modifier;
		Damage(level, power, attack, defense, modifier, damage);
		
	} while (1);
	}

void Damage(double l, double  p, double  a, double  d, double m, double damage) {

	damage = ((2 * l / 5 + 2)*p*a / d / 50 + 2)*m;
	cout << "Damage = " << damage << endl;
}