#pragma once
#include<iostream>

using namespace std;

class Shape {
private:
	// think about the private data members...
	int x;
	int y;
	double l;
	double w;
	double r;
	double area;
	int form; // 1=cirle; 2=square; 3=rectangle; 4=triangle;
	bool test_perpendicular(int, int, int, int, int, int, double);
	double point_area(int, int, int, int, int, int);
	bool test_within(int, int, int, int, int, int, int, int);
public:
	

int getForm() {
	return this->form;
}
void setForm(int form) {
	this->form = form;
}

int getX() {
	return this->x;
}
void setX(int x) {
	this->x = x;
}

int getY() {
	return this->y;
}
void setY(int y) {
	this->y = y;
}

double getL() {
	return this->l;
}
void setL(double l) {
	this->l = l;
}


double getW() {
	return this->w;
}
void setW(double w) {
	this->w = w;
}


double getR() {
	return this->r;
}
void setR(double r) {
	this->r = r;
}

double getArea() {
	return this->area;
}
void setArea(double area) {
	this->area = area;
}

	// provide definitions of following functions...
	Shape();// default constructor
	Shape(int,double,double,int,int);//parameterized constructor that will allow to initialize different types of instances
	Shape(int, double, int, int);
		//implement mutators for all private data members
		//implement accessors for all private data members
		//you have to implement the following functions
		// think about the parameters required and return type of the followingfunctions
	//getArea();//prints area
	bool overlapping(Shape);//determines if two Shapes are overlapping or not
	static Shape returnLargestShape(Shape*&, int);//a static function that returns the largest Shape from the array of Shapes, this functions should only work for the same shapes
	Shape& overlappingShapes(Shape*& S, int j);//a static function that returns an array of Shapes overlapping the largest Shape, this functions should only work for the same shapes
	
	//~Shape();
};
