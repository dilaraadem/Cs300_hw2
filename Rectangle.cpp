//Dilara Ademoðlu
#include "Rectangle.h"
#include <iostream>
#include <vector>
using namespace std;

Rectangle::Rectangle() //default
{
	Top=NULL;
	Left=NULL;
	Bottom=NULL;
	Right=NULL;
	centerX=0;
	centerY=0;
}

void Rectangle::Create(vector<int> rect,int i) //create the rectangle from the input taken from the txt file
{
		Top=rect[i-1];
		Left=rect[i];
		Bottom=rect[i+1];
		Right=rect[i+2];
		centerX=(Left+Right)/2;
		centerY=(Bottom+Top)/2;
}