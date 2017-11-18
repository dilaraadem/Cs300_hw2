//Dilara Ademoglu
#include <iostream>
#include <fstream>
#include <vector>
#include "TwoDimTreeNode.h"
#include "Rectangle.h"
using namespace std;

int main()
{
	int x,y; //points
	ifstream input;
	int word;
	int count;
	TwoDimTreeNode tree;
	Rectangle R;
	vector<Rectangle> data; //store rectangles from the output
	vector<int> coordinates;
	vector<int> rects;
	
	input.open("rectdb.txt");
	while(input>>word) //read from file
	{
		coordinates.push_back(word); //extent rectangle || root tree
	}
	for(int i=4;i<coordinates.size();i++)
		rects.push_back(coordinates[i]); //rectangles
	input.close();

	tree.DefineTree(coordinates); //extent of root

	for(int i=1;i<rects.size()-1;i=i+4) //create all rectangles stored in a vector
	{
		R.Create(rects,i); //create 1 rectangle
		data.push_back(R); //store the rectangle for easy access
	}
	//insert rectangles to linkedlists
	for(int i=0;i<data.size();i++) 
		tree.DivideFourandAdd(data[i],tree); //add rectangle to the tree

	//search point
	cout << "Please enter query points: "<<endl;
	while(cin>> x >> y)//read point	
	{
		cout << endl;
		if(x!=-1)
		{
			vector<Rectangle> rect;
			count=0;
			cout <<"Points are: "<< x << " " << y<< endl; //display points
			tree.SearchTree(x,y,tree,count,rect); //search tree
			cout << "Count is: "<< count << endl; //display number of rectangles
			for(int i=0;i<rect.size();i++) //display coordinates of rectangles
				cout<< rect[i].Top << " " << rect[i].Left << " " << rect[i].Bottom << " "<< rect[i].Right<<endl;
		}
		else
			return 0;
		cout << "Please enter query points: "<<endl;
	}
}
