#pragma once
#include <cmath>

typedef unsigned short pos, dis;

enum NODE_TYPE {
  INVALID,
  WALL,      // flag isChecked as true
  DEAD_END,  // flag isChecked as true
  STRAIGHT,  // only non-node that is not auto isChecked = true;
  NODE,
  START,
  END,
};

struct Position {
  pos PositionX;
  pos PositionY;
};

const Position EMPTY_POSITION = {0, 0};

struct Node {
  bool IsChecked = false;
  NODE_TYPE Type = INVALID;
  dis Distance = 0;
  bool inList = false;
  Position ThisPosition = EMPTY_POSITION;
  Position fromWhere = EMPTY_POSITION;

  Node() = default;
  Node(Position ThisPosition, NODE_TYPE Type, bool IsChecked = false);
  ~Node() = default;
};
//used to calculate the distance form one position to another
inline dis calcDistance(const Position &one, const Position &two) {
  return static_cast<dis>(std::abs((one.PositionX - two.PositionX) +
                                   (one.PositionY - two.PositionY)));
}
