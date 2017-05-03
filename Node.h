#pragma once
#include <cmath>

typedef unsigned short pos, dis;

enum NODE_TPYE
{
	INVALIDE,
	WALL,//auto flag isChecked = true
	DEAD_END, // auto flag isChecked = true 
	STRIGHT, // only non-node that is not auto isChecked = true;
	NODE,
	START,
	END,
};

struct Positon
{
	pos PositionX;
	pos PositionY;
};

const Positon EMPTY_POSITION = {0, 0};


struct  Node
{
	bool isChecked = false;
	NODE_TPYE Type = INVALIDE;
	dis Distance = 0;
	bool inList = false;
	Positon thisPositon = EMPTY_POSITION;
	Positon fromWhere = EMPTY_POSITION;
	
	Node();
	//first pass constructor
	//set ture for nodes that do not need to be check, like dead ends
	Node(Positon ThisPosition, NODE_TPYE Type, bool IsChecked = false);
	~Node();
};

inline dis caclDistance(const Positon& one, const Positon& two)
{
	return abs((one.PositionX - two.PositionX) + (one.PositionY - two.PositionY));
}