#include "Solver.h"

void Solver::FillNodeMap() {
  NodeMap.reserve(static_cast<size_t>(image.TellWidth()));
  for (size_t x = 0; x < image.TellWidth(); x++) {
    NodeMap.push_back(std::vector<Node>());
    NodeMap[x].reserve(static_cast<size_t>(image.TellHeight()));
    for (size_t y = 0; y < image.TellHeight(); y++) {
      NodeMap[x].push_back(Node());
    }
  }

  for (size_t x = 0; x < image.TellWidth(); x++) {
    for (size_t y = 0; y < image.TellHeight(); y++) {
      checkPlace({static_cast<pos>(x), static_cast<pos>(y)});
    }
  }
}

bool Solver::checkNode() {
  while (!nodeQueue.empty()) {
    // first we grab a node off the queue
    const Node &node = nodeQueue.front();
    // ok now we need to look until we find a node, once found we modify it if
    // needed and place it on the queue

    const pos x = node.thisPosition.PositionX;
    const pos y = node.thisPosition.PositionY;

    // looking left
    bool quit = false;
    pos step = 1;
    while (!quit) {
      quit = lookForNextNode(x + step, y, node);
      step++;
    }

    // looking right
    quit = false;
    step = 1;
    while (!quit) {
      quit = lookForNextNode(x - step, y, node);
      step++;
    }

    // looking down
    quit = false;
    step = 1;
    while (!quit) {
      quit = lookForNextNode(x, y + step, node);
      step++;
    }

    // looking up
    quit = false;
    step = 1;
    while (!quit) {
      quit = lookForNextNode(x, y - step, node);
      step++;
    }
    NodeMap[x][y].isChecked = true;
    nodeQueue.pop();
  }

  return false;
}

void Solver::checkPlace(Position nodeLocaion) {
  // so first we need to look at the current color and check if its an end node;
  const pos x = nodeLocaion.PositionX;
  const pos y = nodeLocaion.PositionY;
  RGBApixel color = image.GetPixel(x, y);
  if (color == BLACK) {
    NodeMap[x][y] = Node({x, y}, WALL, true);
    return;
  }
  if (color == BLUE) {
    NodeMap[x][y] = Node({x, y}, END);
    EndNode = {x, y};
    return;
  }
  if (color == RED) {
    NodeMap[x][y] = Node({x, y}, START);
    StartNode = {x, y};
    return;
  }

  // ok now we need see if this pos is a node or not

  bool canMove[4] = {false, false, false, false};
  int numberOfMoves = 0;

  // look left
  color = image.GetPixel(x + 1, y);
  if (!(color == BLACK)) {
    canMove[0] = true;
    numberOfMoves++;
  }

  // right
  color = image.GetPixel(x - 1, y);
  if (!(color == BLACK)) {
    canMove[1] = true;
    numberOfMoves++;
  }

  // down
  color = image.GetPixel(x, y + 1);
  if (!(color == BLACK)) {
    canMove[2] = true;
    numberOfMoves++;
  }

  // up
  color = image.GetPixel(x, y - 1);
  if (!(color == BLACK)) {
    canMove[3] = true;
    numberOfMoves++;
  }

  if (numberOfMoves < 3) {
    if (canMove[0] && canMove[1]) {
      NodeMap[x][y] = Node({x, y}, STRAIGHT);
      return;
    }
    if (canMove[2] && canMove[3]) {
      NodeMap[x][y] = Node({x, y}, STRAIGHT);
      return;
    }
    if (numberOfMoves < 2) {
      NodeMap[x][y] = Node({x, y}, DEAD_END, true);
      return;
    }
  }

  NodeMap[x][y] = Node({x, y}, NODE);
}

bool Solver::lookForNextNode(const pos x, const pos y, const Node &node) {
  // we take a ref
  auto &checking = NodeMap[x][y];
  // assert(checking.Type != INVALID);
  // if the node we are looking at is checked, we stop
  if (checking.isChecked) {
    return true;
  }
  // if the node has a type grader then stright, its a node
  if (checking.Type > STRAIGHT) {
    // we get the distance to the total distance
    const dis totalDistance =
        caclDistance(checking.thisPosition, node.thisPosition) + node.Distance;
    if (!checking.inList) {
      checking.Distance = totalDistance;
      checking.fromWhere = node.thisPosition;
      checking.inList = true;
      nodeQueue.push(checking);
      return true;
    }
    // check to see if the new total distance is less then the one in checking
    if (checking.Distance > totalDistance) {
      // if so, we set the new distance in checking to totalDistance and set
      // fromWhere to node
      // we modify the NodeMap and updata the node where checking was pulled
      // from
      // lastly we add checking to the queue
      checking.Distance = totalDistance;
      checking.fromWhere = node.thisPosition;
      nodeQueue.push(checking);
      return true;
    }
  }
  // the only way it could make it here if it was stright, so we can continue to
  // look
  return false;
}

Position Solver::DrawNodes(const Position name) {
  const Node node = NodeMap[name.PositionX][name.PositionY];
  const Position other = node.fromWhere;

  dis start;
  const dis distance = caclDistance(name, other);
  // draw on y line
  if (name.PositionX == other.PositionX) {
    if (name.PositionY > other.PositionY) {
      start = other.PositionY;
    } else {
      start = name.PositionY;
    }

    for (size_t i = 0; i < distance; i++) {
      image.SetPixel(name.PositionX, static_cast<int>(start + i), GREEN);
    }
  }
  // draw on x line
  else {
    if (name.PositionX > other.PositionX) {
      start = other.PositionX;
    } else {
      start = name.PositionX;
    }

    for (size_t i = 0; i <= distance; i++) {
      image.SetPixel(static_cast<int>(start + i), name.PositionY, GREEN);
    }
  }

  return other;
}

void Solver::start() {
  // place the start node on the queue
  nodeQueue.push(NodeMap[StartNode.PositionX][StartNode.PositionY]);
  // run the queue
  checkNode();

  bool foundEnd = NodeMap[EndNode.PositionX][EndNode.PositionY].isChecked;
  if (!foundEnd) {
    throw NoPathToEnd();
  }
  // draw the nodes

  Position temp = EndNode;
  while (true) {
    temp = DrawNodes(temp);
    if (temp.PositionX == StartNode.PositionX &&
        temp.PositionY == StartNode.PositionY) {
      break;
      ;
    }
  }
  image.SetPixel(StartNode.PositionX, StartNode.PositionY, RED);
  image.SetPixel(EndNode.PositionX, EndNode.PositionY, BLUE);
  SaveFile();
}

Solver::Solver(std::string fileName) {
  Solver::fileName = fileName;
  image.ReadFromFile(fileName.c_str());
  FillNodeMap();
  if (EndNode == EMPTY_POSITION) {
    throw EndNotFoundException();
  }
  if (StartNode == EMPTY_POSITION) {
    throw StartNotFoundException();
  }
}

void Solver::SaveFile() {
  auto i = fileName.find_last_of("/");
  fileName.resize(i);
  std::cout << getFileName().c_str() << '\n';
  std::string output = fileName + getFileName();
  image.WriteToFile(output.c_str());
}

bool operator==(const RGBApixel &left, const RGBApixel &right) {
  return left.Alpha == right.Alpha && left.Blue == right.Blue &&
         left.Green == right.Green && left.Red == right.Red;
}

bool operator==(const Position &left, const Position &right) {
  return left.PositionX == right.PositionX && left.PositionY == right.PositionY;
}

bool operator!=(const Position &left, const Position &right) {
  return left.PositionX != right.PositionX || left.PositionY != right.PositionY;
}
