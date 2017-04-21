#include <iostream>
#include <ctime>
using namespace std;

void Colors();

int main() {

	do {
		srand(time(NULL));
		Colors();
		system("PAUSE");
	} while (1);
}

void Colors() {
		int num = rand() % 100 + 1;

		if (num <= 25) {
			system("Color 1F");
		}
		else if (num > 25 && num <= 50) {
			system("Color 2F");
			
		}
		else if (num > 50 && num <= 100) {
			system("Color 4F");
			
		}
}