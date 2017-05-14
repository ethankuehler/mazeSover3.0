#pragma once
#include "FileName.h"
#include "Node.h"
#include "easyBMP/EasyBMP.h"
#include <exception>
#include <queue>
#include <vector>

const RGBApixel RED = {0x00, 0x00, 0xff, 0x00};
const RGBApixel GREEN = {0x00, 0xff, 0x00, 0x00};
const RGBApixel BLUE = {0xff, 0x00, 0x00, 0x00};
const RGBApixel BLACK = {0x00, 0x00, 0x00, 0x00};

bool operator==(const RGBApixel &left, const RGBApixel &right);
bool operator==(const Position &left, const Position &right);
bool operator!=(const Position &left, const Position &right);

<<<<<<< HEAD
struct Solver
{
	//a 2d vector of nodes, the position of each node is drectly coarspoing to its location on the image
	std::vector<std::vector<Node> > NodeMap;
	//a queue of nodes to be checked by the func checkNode, nodes are pushed and poped by looKforNextNode who is called by checkNode; 
	std::queue<Node> nodeQueue;
	//the raw image data, only to be modified by drawNodes
	BMP image;
=======
struct Solver {
  // a 2d vector of nodes, the position of each node is drectly coarspoing to
  // its location on the image
  std::vector<std::vector<Node>> NodeMap;
  // a queue of nodes to be checked by the func checkNode, nodes are pushed and
  // poped by looKforNextNode who is called by checkNode;
  std::queue<Node> nodeQueue;
  // the raw image data, only to be modified by drawNodes
  BMP image;

  Position EndNode = EMPTY_POSITION;
  Position StartNode = EMPTY_POSITION;

  std::string fileName;

  // fills the node map with nodes
  void FillNodeMap();
>>>>>>> origin/LIB

  // check a node on the node queue, findes other nods the check and pops off
  // old ones;
  bool checkNode();

<<<<<<< HEAD
    std::string fileName;


	//fills the node map with nodes
	void FillNodeMap();
=======
  // check a place to see what type/if a positon is a node, only called my
  // fillNodeMap;
  void checkPlace(Position nodeLocaion);
>>>>>>> origin/LIB

  // look to see if position given is a node, if so it will diced if its neede
  // to be modifyed. only called by checkNode
  bool lookForNextNode(pos x, pos y, const Node &node);

  // give it the end node and it will draw from there
  Position DrawNodes(Position name);

  // starts the solveing
  void start();

  void SaveFile();

<<<<<<< HEAD
	//starts the solveing
	void start();

    void SaveFile();

	//louds the map, fill the NodeMaze. can throw
	Solver(std::string fileName);

	~Solver() = default;


=======
  // louds the map, fill the NodeMaze. can throw
  Solver(std::string fileName);

  ~Solver() = default;
>>>>>>> origin/LIB
};

struct StartNotFoundException : public std::exception {
  const char *what() const throw() { return "start not found exception"; }
};

struct EndNotFoundException : public std::exception {
  const char *what() const throw() { return "end not found exception"; }
};

struct NoPathToEnd : public std::exception {
  const char *what() const throw() { return "no path from start to end"; }
};
