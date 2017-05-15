#include <iostream>
using namespace std;

int main() {
	char input;
	int smash=0;
	int minecraft=0;
	int mariokart=0;

	do {

		cout << "Do You Like Fighting? (type either 'y' or 'n') or press 'q' to quit." << endl;
		cin >> input;
		if (input == 'y') {
			smash++;
		}
		else if (input == 'n') {
			cout << "okay" << endl;
		}
		cout << "Do You Like Building?" << endl;
		cin >> input;
		if (input == 'y') {
			minecraft++;
		}
		else if (input == 'n') {
			cout << "okay" << endl;
		}
		cout << "Do you like racing?" << endl;
		cin >> input;
		if (input == 'y') {
			mariokart++;
		}
		else if (input == 'n') {
			cout << "okay" << endl;
		}

		if (smash > minecraft && smash > mariokart) {
			cout << "We should continue to play smash" << endl;
		}
		if (minecraft > smash && minecraft > mariokart) {
			cout << "We should play minecraft" << endl;
		}
		if (mariokart > smash && mariokart > minecraft) {
			cout << "We should play mariokart" << endl;
		}

	} while (input != 'q');

}