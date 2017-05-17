#include "Node.h"

Node::Node(Position ThisPosition, NODE_TYPE Type, bool IsChecked) {
  Node::ThisPosition = ThisPosition;
  Node::Type = Type;
  Node::IsChecked = IsChecked;
}
