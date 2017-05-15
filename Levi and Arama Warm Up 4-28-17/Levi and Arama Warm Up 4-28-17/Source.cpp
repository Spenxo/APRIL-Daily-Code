#include <iostream>
using namespace std;
void nuke(double BAS, double OrbAmount, double Nuke);
int main() {
	double BAS;
	double OrbAmount;
	double Nuke =0;
	cout << "Enter a number for the base attack stat." << endl;
	cin >> BAS;
	cout << "Now enter a number for the orb amount." << endl;
	cin >> OrbAmount;
	nuke(BAS, OrbAmount, Nuke);

}
void nuke(double BAS, double OrbAmount, double Nuke) {
	Nuke = BAS * (1 + (0.3 * OrbAmount)) + 3000;
	cout << Nuke << endl;
}