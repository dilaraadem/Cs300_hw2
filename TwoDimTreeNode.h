//Dilara Ademoðlu
#ifndef _TWODIMTREENODE_H
#define _TWODIMTREENODE_H

#include <iostream>
#include <vector>
#include "Rectangle.h"
#include "LinkedListTemplate.h"

using namespace std;

class TwoDimTreeNode{
public:
	TwoDimTreeNode();//default constructor
	void DefineTree(vector<int> num); //outer boundary
	void DivideFourandAdd(Rectangle & R,TwoDimTreeNode &node);	//insert to linkedlist
	void SearchTree(int x,int y,TwoDimTreeNode& node,int &count,vector<Rectangle> &rect); //search
	void CreateNode(TwoDimTreeNode &node); //create topleft,topright,bottomleft,bottomright of that extent
private:
	Rectangle Extent;
	LinkedList<Rectangle> Vertical, Horizontal;
	TwoDimTreeNode *TopLeft, *TopRight, *BottomLeft, *BottomRight;
};
#endif