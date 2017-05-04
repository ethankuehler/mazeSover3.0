#pragma once
#include <cmath>

typedef unsigned short pos, dis;

enum NODE_TYPE
{
    INVALID,
	WALL,//auto flag isChecked = true
	DEAD_END, // auto flag isChecked = true 
    STRAIGHT, // only non-node that is not auto isChecked = true;
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
	NODE_TYPE Type = INVALID;
	dis Distance = 0;
	bool inList = false;
	Positon thisPosition = EMPTY_POSITION;
	Positon fromWhere = EMPTY_POSITION;
	
	Node();
	//first pass constructor
	//set true for nodes that do not need to be check, like dead ends
	Node(Positon ThisPosition, NODE_TYPE Type, bool IsChecked = false);
	~Node();
};

inline dis caclDistance(const Positon& one, const Positon& two)
{
	return static_cast<dis>(abs((one.PositionX - two.PositionX) + (one.PositionY - two.PositionY)));
}
