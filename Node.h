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

struct Position
{
	pos PositionX;
	pos PositionY;
};

const Position EMPTY_POSITION = {0, 0};

struct  Node
{
	bool isChecked = false;
	NODE_TYPE Type = INVALID;
	dis Distance = 0;
	bool inList = false;
	Position thisPosition = EMPTY_POSITION;
	Position fromWhere = EMPTY_POSITION;
	
	Node() = default;
	//first pass constructor
	//set true for nodes that do not need to be check, like dead ends
	Node(Position ThisPosition, NODE_TYPE Type, bool IsChecked = false);
	~Node() = default;
};

inline dis caclDistance(const Position& one, const Position& two)
{
	return static_cast<dis>(std::abs((one.PositionX - two.PositionX) + (one.PositionY - two.PositionY)));
}
