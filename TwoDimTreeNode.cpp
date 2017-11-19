//Dilara Ademoðlu
#include "TwoDimTreeNode.h"
#include <iostream>
using namespace std;

TwoDimTreeNode::TwoDimTreeNode() //default
{
	TopLeft=NULL;
	TopRight=NULL;
	BottomLeft=NULL;
	BottomRight=NULL;
}

void TwoDimTreeNode::DefineTree(vector<int> num) //write first line as outer boundary
{
	this->Extent.Top=num[0];
	this->Extent.Left=num[1];
	this->Extent.Bottom=num[2];
	this->Extent.Right=num[3];
	this->Extent.centerX=(num[1]+num[3])/2;
	this->Extent.centerY=(num[0]+num[2])/2;
}

void TwoDimTreeNode::CreateNode(TwoDimTreeNode &node) //divide current extent to 4
{
	if(node.TopLeft==NULL)
	{
		node.TopLeft=new TwoDimTreeNode;
		node.TopLeft->Extent.Top=node.Extent.Top;
		node.TopLeft->Extent.Left=node.Extent.Left;
		node.TopLeft->Extent.Bottom=(node.Extent.Top+node.Extent.Bottom)/2;
		node.TopLeft->Extent.Right=(node.Extent.Left+node.Extent.Right)/2;
		node.TopLeft->Extent.centerX=(node.TopLeft->Extent.Right+node.TopLeft->Extent.Left)/2;
		node.TopLeft->Extent.centerY=(node.TopLeft->Extent.Top+node.TopLeft->Extent.Right)/2;
	}
	if(node.TopRight==NULL)
	{
		node.TopRight=new TwoDimTreeNode;
		node.TopRight->Extent.Top=node.Extent.Top;
		node.TopRight->Extent.Left=((node.Extent.Left+node.Extent.Right)/2)+1;
		node.TopRight->Extent.Bottom=(node.Extent.Top+node.Extent.Bottom)/2;
		node.TopRight->Extent.Right=node.Extent.Right;
		node.TopRight->Extent.centerX=(node.TopRight->Extent.Right+node.TopRight->Extent.Left)/2;
		node.TopRight->Extent.centerY=(node.TopRight->Extent.Top+node.TopRight->Extent.Bottom)/2;
	}
	if(node.BottomLeft==NULL)
	{
		node.BottomLeft=new TwoDimTreeNode;
		node.BottomLeft->Extent.Top=((node.Extent.Top+node.Extent.Bottom)/2)+1;
		node.BottomLeft->Extent.Left=node.Extent.Left;
		node.BottomLeft->Extent.Bottom=node.Extent.Bottom;
		node.BottomLeft->Extent.Right=(node.Extent.Left+node.Extent.Right)/2;
		node.BottomLeft->Extent.centerX=(node.BottomLeft->Extent.Right+node.BottomLeft->Extent.Left)/2;
		node.BottomLeft->Extent.centerY=(node.BottomLeft->Extent.Top+node.BottomLeft->Extent.Bottom)/2;
	}
	if(node.BottomRight==NULL)
	{
		node.BottomRight=new TwoDimTreeNode;
		node.BottomRight->Extent.Top=((node.Extent.Top+node.Extent.Bottom)/2)+1;
		node.BottomRight->Extent.Left=((node.Extent.Left+node.Extent.Right)/2)+1;
		node.BottomRight->Extent.Bottom=node.Extent.Bottom;
		node.BottomRight->Extent.Right=node.Extent.Right;
		node.BottomRight->Extent.centerX=(node.BottomRight->Extent.Right+node.BottomRight->Extent.Left)/2;
		node.BottomRight->Extent.centerY=(node.BottomRight->Extent.Top+node.BottomRight->Extent.Bottom)/2;
	}
}

void TwoDimTreeNode::DivideFourandAdd(Rectangle &R,TwoDimTreeNode &node) //insert
{
	if(R.Left<=node.Extent.centerX && R.Right<node.Extent.centerX && R.Bottom>node.Extent.centerY && R.Top<=node.Extent.centerY)
	{ //check if rectangle intersects both lines
		node.Vertical.add(R);
	}
	else if(R.Left<=node.Extent.centerX && R.Right>node.Extent.centerX)
	{//check if rectangle is on vertical/centerX
		node.Vertical.add(R);
	}
	else if(R.Bottom>node.Extent.centerY && R.Top<=node.Extent.centerY)
	{//check if rectangle is on horizontal/centerY
		node.Horizontal.add(R);
	}
	else //if not, then rectangle is a level down, check for all 4 nodes
	{
		if(R.Right<node.Extent.centerX && R.Bottom<node.Extent.centerY)//add topleft node
		{
			CreateNode(node); //create all four nodes (divide to 4)
			DivideFourandAdd(R,*node.TopLeft); //add the rectangle recursively in the node
		}
		else if(node.Extent.centerX<R.Left && node.Extent.centerY>R.Bottom)//add topright node
		{
			CreateNode(node);
			DivideFourandAdd(R,*node.TopRight);
		}
		else if(R.Right<node.Extent.centerX && node.Extent.centerY<R.Top)//add bottomleft node
		{
			CreateNode(node);
			DivideFourandAdd(R,*node.BottomLeft);
		}
		else if(R.Left>node.Extent.centerX && node.Extent.centerY<R.Top)//add bottomright node
		{
			CreateNode(node);
			DivideFourandAdd(R,*node.BottomRight);
		}
	}
}

void TwoDimTreeNode::SearchTree(int x, int y,TwoDimTreeNode &root, int &count,vector<Rectangle> &rect) //search
{
	node<Rectangle> *ptr=root.Vertical.head;
	node<Rectangle>*p=root.Horizontal.head;

	if(root.Vertical.size!=0 || root.Horizontal.size!=0) //compare x and y with rectangles
	{
		if(root.Vertical.size!=0) //find rectangles that match with point on vertical list
		{
			while(ptr!=NULL)
			{
				if(x<ptr->info.Right && y<ptr->info.Bottom && ptr->info.Top<=y && ptr->info.Left<=x) //check if point is on that rectangle
				{
					count++; //increase count
					rect.push_back(ptr->info); //store the found rectangle's info
				}
				if(root.TopLeft!=NULL || root.TopRight!=NULL || root.BottomLeft!=NULL || root.BottomRight!=NULL) 
					//check if there are other rectangles a level down, recursively
				{
					if(x<root.Extent.centerX && y<root.Extent.centerY)
						SearchTree(x,y,*root.TopLeft,count,rect);
					else if(root.Extent.centerX<x && root.Extent.centerY>y)
						SearchTree(x,y,*root.TopRight,count,rect);
					else if(x<root.Extent.centerX && root.Extent.centerY<y)
						SearchTree(x,y,*root.BottomLeft,count,rect);
					else if(x>root.Extent.centerX && root.Extent.centerY<y)
						SearchTree(x,y,*root.BottomRight,count,rect);
				}
				ptr=ptr->next;
			}
		}
		if(root.Horizontal.size!=0) //find rectangles that match with pont on horizontal list
		{
			while(p!=NULL) //if there are more than 1 rectangles on the same linkedlist,check all
			{
				if(x<p->info.Right && y<p->info.Bottom && p->info.Top<=y && p->info.Left<=x)
				{
					count++; //increase count
					rect.push_back(p->info); //store the found rectangle's info
				}
				if(root.TopLeft!=NULL || root.TopRight!=NULL || root.BottomLeft!=NULL || root.BottomRight!=NULL)
				//check if there are other rectangles a level down, recursively
				{
					if(x<root.Extent.centerX && y<root.Extent.centerY)
						SearchTree(x,y,*root.TopLeft,count,rect);
					else if(root.Extent.centerX<x && root.Extent.centerY>y)
						SearchTree(x,y,*root.TopRight,count,rect);
					else if(x<root.Extent.centerX && root.Extent.centerY<y)
						SearchTree(x,y,*root.BottomLeft,count,rect);
					else if(x>root.Extent.centerX && root.Extent.centerY<y)
						SearchTree(x,y,*root.BottomRight,count,rect);
				}
				p=p->next;
			}
		}
	}
	else//if there are no rectangles to match go a level down, meaning vertical and horizontal sizes are 0
	{
		if(root.TopLeft!=NULL || root.TopRight!=NULL || root.BottomLeft!=NULL || root.BottomRight!=NULL)
		{
			if(x<root.Extent.centerX && y<root.Extent.centerY)
				SearchTree(x,y,*root.TopLeft,count,rect);
			if(root.Extent.centerX<x && root.Extent.centerY>y)
				SearchTree(x,y,*root.TopRight,count,rect);
			if(x<root.Extent.centerX && root.Extent.centerY<y)
				SearchTree(x,y,*root.BottomLeft,count,rect);
			if(x>root.Extent.centerX && root.Extent.centerY<y)
				SearchTree(x,y,*root.BottomRight,count,rect);
		}
	}
}
