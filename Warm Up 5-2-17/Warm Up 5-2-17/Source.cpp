#include <iostream>
#include <string>
using namespace std;

int main() {

	do {
		string foods[7] = { "pizza, ", "ice cream, ", "bacon, ", "jalepeno, ", "chocolate, ", "pickle, ", "takis, " };

		for (int i = 0; i < 7; i++) {
			cout << foods[i] << endl;
		}
		system("PAUSE");
	} while (1);
}