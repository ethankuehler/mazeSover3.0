#include "Node.h"

Node::Node(Position ThisPosition, NODE_TYPE Type, bool IsChecked) {
  Node::thisPosition = ThisPosition;
  Node::Type = Type;
  Node::isChecked = IsChecked;
}
