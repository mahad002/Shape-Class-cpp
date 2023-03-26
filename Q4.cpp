#include "Shape.h"
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	cout << "Hello World!" << endl;
	bool check;
	Shape S1(1, 10, 2, 2);
	Shape S2(3, 10, 2, 3, 4);
	Shape* arr = new Shape[2];
	arr[0] = S1;
	arr[1] = S2;
	check=S1.overlapping(S2);
	if (check) {
		cout << "Shapes Overlap!\n";
	}
	else {
		cout << "Shapes Don't Overlap!\n";
	}

	Shape* S = new Shape[4];
	for (int i = 0; i < 4; i++) {
		S[i].setForm((rand() % 4) + 1);
		if (S[i].getForm() == 3) {
			S[i].setL((rand() % 20) + 1);
			S[i].setW((rand() % 20) + 1);
			S[i].setR(0);
			S[i].setArea(S[i].getL() * S[i].getW());

		}
		else if (S[i].getForm() == 1) {
			S[i].setL(0);
			S[i].setW(0);
			S[i].setR((rand() % 20) + 1);
			S[i].setArea(3.142 * pow(S[1].getR(), 2));
		}
		else if (S[i].getForm() == 4) {
			S[i].setL((rand() % 20) + 1);
			S[i].setW((rand() % 20) + 1);
			S[i].setR(0);
			S[i].setArea(0.5 * S[i].getL() * S[i].getW());

		}
		else if (S[i].getForm() == 2) {
			S[i].setL((rand() % 20) + 1);
			S[i].setW(S[i].getL());
			S[i].setR(0);
			S[i].setArea(S[i].getL() * S[i].getW());
		}
		S[i].setX(rand() % 20);
		S[i].setY(rand() % 20);
	}
	Shape Large = Shape::returnLargestShape(S,4);

	Shape S3 = S1.overlappingShapes(arr, 2);

	cout << Large.getArea() << endl;

	return 0;
}

