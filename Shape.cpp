#include "Shape.h"
#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

Shape::Shape() {
	l = 0;
	w = 0;
	r = 0;
	area = 0;
	form = 0;
	//coordinates = NULL;
	x = 0;
	y = 0;
}

Shape::Shape(int a, double b, double c, int d, int e) {
	form = a;

	l = b;
	w = c;
	r = 0;
	if (form == 3) {
		area = l * w;
		x = d;
		y = e;

	}
	else if (form == 4) {
		area = (l * w) / 2.0;
		x = d;
		y = e;
	}
}

Shape:: Shape(int a, double b, int c, int d) {
	form = a;
	if (form == 1) {
		r = b;
		area = 3.142 * b * b;
		l = 0;
		w = 0;
		x = c;
		y = d;
	}
	else if (form == 2) {
		l = b;
		w = b;
		r = 0;
		area = l * w;
		x = c;
		y = d;

	}
}

bool Shape::test_perpendicular(int x, int x1, int xc, int y, int y1, int yc, double r) {
	double m = double(x - x1) /(y - y1);
	double mt = -1 / m;
	//y-y1=m(x-x1);
	//y-yc=mt(x-xc);
	double xt = ((m * x1) - y1 + yc - (mt * xc)) / (m - mt);
	double yt = m * (xt - x1) + y1;
	return (r > pow((pow((xt - xc), 2) + pow((yt - yc), 2)), 1/2.0));
}

double Shape :: point_area(int x1, int x2, int x3, int y1, int y2, int y3) {
	double area = ((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
	if (area > 0) {
		//cout << "Area: " << area << endl;

		return area;
	}
	else {
		area *= -1;
		//cout << "Area: " << area << endl;

		return area;
	}
}
//int x, int x1, int x2, int x3, int y, int y1, int y2, int y3
//int x1, int y1, int x2, int y2, int x3, int y3, int x, int y
//(test_within(x, y, x + w, y, x + (w / 2), y + l, S1.x, S1.y) || test_within(x, y, x + w, y, x + (w / 2), y + l, S1.x + S1.w, S1.y))
//(test_within(S1.x, S1.y, S1.x + S1.w, S1.y, S1.x + (S1.w / 2), S1.y + S1.l, x, y) || test_within(S1.x, S1.y, S1.x + S1.w, S1.y, S1.x + (S1.w / 2), S1.y + S1.l, x + w, y))


bool Shape::test_within(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y) {
	bool check = false;
	/* Calculate area of complete triangle*/
	double area, area1, area2, area3, total_area;
	area=point_area(x1,x2,x3,y1,y2,y3);
	area1= point_area(x,x2,x3, y,y2,y3);
	area2= point_area(x1,x,x3, y1,y,y3);
	area3 = point_area(x1,x2,x,y1,y2,y);
	total_area = area1 + area2 + area3;
	if (total_area == area) {
		check = true;
		return check;
	}
	return check;
}

bool Shape::overlapping(Shape S1) {
	bool check = false;
	//1.Circle - Circle;
	if (form == 1 && S1.form == 1) {
		cout << "Circle-Circle\n";
		int c1, c2;
		c1 = ((x - S1.x) * (x - S1.x)) + ((y - S1.y) * (y - S1.y));
		c2 = (pow((r + S1.r), 2));
		if (c1 < c2) {
			check = true;
			return check;
		}
		else {
			return check;
		}
	}
	//2.Triangle - Triangle;
	else if (form == 4 && S1.form == 4) {
		cout << "Triangle -Triangle\n";
		if (x > (S1.x + S1.w) || (x + w) < S1.x) {
			//cout << "2\n";
			return check;
		}
		else  if ((y + l) < S1.y || (S1.y + S1.l) < y) {
			//cout << "3\n";
			return check;
		}
		else {
			if ((y > S1.y) && ((x > ((S1.x + S1.w) / 2)) || (x + w) < ((S1.x + S1.w) / 2))) {
				if (test_within(x,y, x + w,y, x + (w / 2), y + l, S1.x, S1.y) || test_within(x,y, x + w,y, x + (w / 2), y + l, S1.x + S1.w, S1.y)) {
					check = true;
					return check;
				}
			}
			else if ((y < S1.y) && ((((x + w) / 2) < S1.x) || ((x + w) / 2) > (S1.x + S1.w))) {
				if (test_within(S1.x,S1.y, S1.x + S1.w,S1.y, S1.x + (S1.w / 2), S1.y + S1.l,x,y) || test_within( S1.x,S1.y, S1.x + S1.w,S1.y, S1.x + (S1.w / 2),S1.y + S1.l, x + w, y)) {
					check = true;
					return check;
				}
			}
			else {
				check = true;

			}
		}
	}
	//3.Square / Rectangle - Square / Rectangle;
	else if ((form == 2 || form == 3) && (S1.form == 2 || S1.form == 3)) {
		cout << "Square / Rectangle - Square / Rectangle\n";
		if (x > (S1.x + S1.w) || (x + w) < S1.x) {
			//cout << "2\n";
			return check;
		}
		else  if ((y + l) < S1.y || (S1.y + S1.l) < y) {
			//cout << "3\n";
			return check;
		}
		else {
			check = true;
			return check;
		}
	}
	//4.Square / Rectangle - Circle;
	else if (((form == 2 || form == 3) && S1.form == 1) || ((S1.form == 2 || S1.form == 3) && form == 1)) {
		if (form == 1) {
			//cout << "Yoooo!\n";
			Shape temp = *this;
			*this = S1;
			S1 = temp;
		}
		double px=0, py=0;

		if (S1.x > x + w) {
			px = x + w;
		}
		else if (S1.x < x + w) {
			px = S1.x;
		}
		if (px < x) {
			px = x;
		}

		if (S1.y > y + l) {
			px = y + l;
		}
		else if (S1.y < y + l) {
			px = S1.y;
		}
		if (px < y) {
			px = y;
		}

		px -= S1.x;
		py -= S1.y;
		if (pow(S1.r, 2) > pow(px, 2) + pow(py, 2)) { //pow(c,2)=pow(a,2)+pow(b,2)
			check = true;
			return check;
		}
	}
	//5.Square / Rectangle - Triangle;
	else if (((form == 2 || form == 3) && S1.form == 4) || ((S1.form == 2 || S1.form == 3) && form == 4)) {
		cout << "Square / Rectangle - Triangle\n";
		if (form == 4) {
			//cout << "Yoooo!\n";
			Shape temp = *this;
			*this = S1;
			S1 = temp;
		}
		if (x > (S1.x + S1.w) || (x + w) < S1.x) {
			//cout << "2\n";
			return check;
		}
		else  if ((y + l) < S1.y || (S1.y + S1.l) < y) {
			//cout << "3\n";
			return check;
		}
		else if (test_within(S1.x + S1.w, S1.y, S1.x + (S1.w / 2),S1.y +S1.l, S1.x,S1.y,x, y ) || test_within( S1.x + S1.w,S1.y, S1.x + (S1.w / 2),S1.y + S1.l, S1.x, S1.y, x + w, y)) {
				check = true;
				return check;
			}
		else {
			check = true;
			return check;
		}
		
	}
	//6.Circle - Triangle;
	else if ((form == 1 && S1.form == 4) || (S1.form == 1 && form == 4)) {
	if (form == 4) {
		//cout << "Yoooo!\n";
		Shape temp = *this;
		*this = S1;
		S1 = temp;
	}
		double px=0, py=0;

		if (S1.x > x + w) {
			px = x + w;
		}
		else if (S1.x < x + w) {
			px = S1.x;
		}
		if (px < x) {
			px = x;
		}

		if (S1.y > y + l) {
			px = y + l;
		}
		else if (S1.y < y + l) {
			px = S1.y;
		}
		if (px < y) {
			px = y;
		}
		px -= S1.x;
		py -= S1.y;
		if (pow(S1.r, 2) > pow(px, 2) + pow(py, 2)) { //pow(c,2)=pow(a,2)+pow(b,2)
			if ((S1.y > y && S1.x > x + (w / 2)) && (test_perpendicular(x + (w / 2), x + w, S1.x, y + l, y, S1.y, S1.r))) {
				check = true;
				return check;
			}
			else if ((S1.y > y && S1.x < x + (w / 2)) && (test_perpendicular(x, x + (w / 2), S1.x, y, y + l, S1.y, S1.r))) {
				check = true;
				return check;
			}
		}
	}
	else {
		cout << "OK!\n";
	}
	
	return check;

}

Shape& Shape::overlappingShapes(Shape*& S, int j) {
	Shape max = returnLargestShape(S, j);
	int x = 0;
	for (int i = 0; i < j; i++) {
		if (max.overlapping(S[i]) && (max.form == S[i].form)) {
			x++;
		}
	}
	Shape* OLS = new Shape[x];
	x = 0;
	for (int i = 0; i < j; i++) {
		if (max.overlapping(S[i]) && (max.form == S[i].form)) {
			OLS[x] = S[i];
			x++;
		}
	}
	cout << "x: " << x << endl;
	return (*OLS);
}

Shape Shape :: returnLargestShape(Shape*& S1, int index) {
	Shape Ans = S1[0];
	double max = S1[0].getArea();

	for (int i = 0; i < index; i++) {
		if (max <= S1[i].getArea()) {
			Ans = S1[i];
			max = S1[i].getArea();
		}
	}
	return Ans;
}
