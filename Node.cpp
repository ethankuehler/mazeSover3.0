#include "Node.h"


Node::Node()
{
}


Node::Node(Positon ThisPosition, NODE_TYPE Type, bool IsChecked)
{
	Node::thisPosition = ThisPosition;
	Node::Type = Type;
	Node::isChecked = IsChecked;
}

Node::~Node()
{
}
