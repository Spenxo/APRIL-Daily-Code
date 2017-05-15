#include <iostream>
#include <ctime>
using namespace std;

int main() {
	do {
		srand(time(NULL));
		int generator[7] = { 0,0,0,0,0,0,0 };

		for (int i = 0; i <= 7; i++) {
			generator[i] = rand() % 10 + 1;
		}
		cout << "generator = {" << generator[1] << ", " << generator[2] << ", " << generator[3] << ", " << generator[4] << ", " << generator[5] << ", " << generator[6] << ", " << generator[7] << "}" << endl;
	} while (1);
}