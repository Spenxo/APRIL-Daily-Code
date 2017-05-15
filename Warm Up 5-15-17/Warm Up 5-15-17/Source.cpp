#include <iostream>
using namespace std;
#include <string>
#include <ctime>

int main() {
	do {
		srand(time(NULL));
		string NPC[10]{ "Hey Boy, Let's get goin'", "MASON!", "I'm gonna kill you","Don't shoot, we're alive","Let it rip mason","Dragovich","Krevchanko","Steiner","These 'men' ","MUST DIE" };
		int num = rand() % 10;

		if (num == 1) {
			cout << NPC[1] << endl;
		}
		if (num == 2) {
			cout << NPC[2] << endl;
		}
		if (num == 3) {
			cout << NPC[3] << endl;
		}
		if (num == 4) {
			cout << NPC[4] << endl;
		}
		if (num == 5) {
			cout << NPC[5] << endl;
		}
		if (num == 6) {
			cout << NPC[6] << endl;
		}
		if (num == 7) {
			cout << NPC[7] << endl;
		}
		if (num == 8) {
			cout << NPC[8] << endl;
		}
		if (num == 9) {
			cout << NPC[9] << endl;
		}
		if (num == 10) {
			cout << NPC[10] << endl;
		}

	} while (1);

}