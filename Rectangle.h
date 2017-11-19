//Dilara Ademoðlu
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include <iostream>
#include <vector>
using namespace std;

class Rectangle
{	
public:
	int Top, Left, Bottom, Right;
	Rectangle();//default
	void Create(vector<int> rect,int i); //create a rectangle object
	int centerX, centerY; //center points
};
#endif