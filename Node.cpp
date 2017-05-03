#include "Node.h"


Node::Node()
{
}


Node::Node(Positon ThisPosition, NODE_TPYE Type, bool IsChecked)
{
	Node::thisPositon = ThisPosition;
	Node::Type = Type;
	Node::isChecked = IsChecked;
}

Node::~Node()
{
}


