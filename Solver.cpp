#include "Solver.h"


void Solver::FillNodeMap()
{
	NodeMap.reserve(image.TellWidth());
	for (size_t x = 0; x < image.TellWidth(); x++)
	{
		NodeMap.push_back(std::vector<Node>());
		NodeMap[x].reserve(image.TellHeight());
		for (size_t y = 0; y < image.TellHeight(); y++)
		{
			NodeMap[x].push_back(Node());
		}
	}

	for (size_t x = 0; x < image.TellWidth() ; x++)
	{
		for (size_t y = 0; y < image.TellHeight() ; y++)
		{
			checkPlace({ static_cast<pos>(x), static_cast<pos>(y) });
		}
	}
}

bool Solver::checkNode()
{
	while (!nodeQueue.empty())
	{
		//first we grab a node off the queue
		const Node& node = nodeQueue.front();
		//ok now we need to look until we find a node, once found we modify it if needed and place it on the queue

		const pos x = node.thisPositon.PositionX;
		const pos y = node.thisPositon.PositionY;

		//looking left
		bool quit = false;
		pos step = 1;
		while (!quit)
		{
			quit = lookForNextNode(x + step, y, node);
			step++;
		}

		//looking right
		quit = false;
		step = 1;
		while (!quit)
		{
			quit = lookForNextNode(x - step, y, node);
			step++;
		}

		//looking down
		quit = false;
		step = 1;
		while (!quit)
		{
			quit = lookForNextNode(x, y + step, node);
			step++;
		}

		//looking up
		quit = false;
		step = 1;
		while (!quit)
		{
			quit = lookForNextNode(x, y - step, node);
			step++;
		}
		NodeMap[x][y].isChecked = true;
		nodeQueue.pop();
	}
	
	return false;
}

void Solver::checkPlace(Positon nodeLocaion)
{
	//so first we need to look at the current color and check if its an end node;
	const pos x = nodeLocaion.PositionX;
	const pos y = nodeLocaion.PositionY;
	RGBApixel color = image.GetPixel(x, y);
	if (color == BLACK)
	{
		NodeMap[x][y] = Node({ x,y }, WALL, true);
		return;
	}
	if (color == BLUE)
	{
		NodeMap[x][y] = Node({ x,y }, END);
		EndNode = { x,y };
		return;
	}
	if (color == RED)
	{
		NodeMap[x][y] = Node({ x,y }, START);
		StartNode = { x,y };
		return;
	}

	//ok now we need see if this pos is a node or not

	bool canMove[4] = { false, false, false ,false };
	int numberOfMoves = 0;

	//look left
	color = image.GetPixel(x + 1, y);
	if (!(color == BLACK))
	{
		canMove[0] = true;
		numberOfMoves++;
	}

	//right
	color = image.GetPixel(x - 1, y);
	if (!(color == BLACK))
	{
		canMove[1] = true;
		numberOfMoves++;
	}

	//down
	color = image.GetPixel(x, y + 1);
	if (!(color == BLACK))
	{
		canMove[2] = true;
		numberOfMoves++;
	}

	//up
	color = image.GetPixel(x, y - 1);
	if (!(color == BLACK))
	{
		canMove[3] = true;
		numberOfMoves++;
	}

	if (numberOfMoves < 3)
	{
		if (canMove[0] == true && canMove[1] == true)
		{
			NodeMap[x][y] = Node({ x, y }, STRIGHT);
			return;
		}
		if (canMove[2] == true && canMove[3] == true)
		{
			NodeMap[x][y] = Node({ x, y }, STRIGHT);
			return;
		}
		if (numberOfMoves < 2)
		{
			NodeMap[x][y] = Node({ x, y }, DEAD_END, true);
			return;
		}
	}

	NodeMap[x][y] = Node({ x,y }, NODE);
}

bool Solver::lookForNextNode(const pos x,const  pos y, const Node& node)
{
	//we take a ref
	auto& checking = NodeMap[x][y];
	//assert(checking.Type != INVALIDE);
	//if the node we are looking at is checked, we stop 
	if (checking.isChecked == true)
	{
		return true;
	}
	//if the node has a type grader then stright, its a node
	if (checking.Type > STRIGHT)
	{
		//we get the distance to the total distance
		const dis totalDistance = caclDistance(checking.thisPositon, node.thisPositon) + node.Distance;
		if (!checking.inList)
		{
			checking.Distance = totalDistance;
			checking.fromWhere = node.thisPositon;
			checking.inList = true;
			nodeQueue.push(checking);
			return true;
		}
		//check to see if the new total distance is less then the one in checking
		if (checking.Distance > totalDistance)
		{
			//if so, we set the new distance in checking to totalDistance and set fromWhere to node
			//we modify the NodeMap and updata the node where checking was pulled from
			//lastly we add checking to the queue
			checking.Distance = totalDistance;
			checking.fromWhere = node.thisPositon;
			nodeQueue.push(checking);
			return true;
		}

	}
	//the only way it could make it here if it was stright, so we can continue to look
	return false;
}

Positon Solver::DrawNodes(const Positon name)
{
	const Node node = NodeMap[name.PositionX][name.PositionY];
	const Positon other = node.fromWhere;

	dis start;
	const dis distance = caclDistance(name, other);
	//draw on y line
	if (name.PositionX == other.PositionX)
	{
		if (name.PositionY > other.PositionY)
		{
			start = other.PositionY;
		}
		else
		{
			start = name.PositionY;
		}

		for (size_t i = 0; i < distance; i++)
		{
			image.SetPixel(name.PositionX, start + i, GREEN);
		}
	}
	//draw on x line
	else
	{
		if (name.PositionX > other.PositionX)
		{
			start = other.PositionX;
		}
		else
		{
			start = name.PositionX;
		}

		for (size_t i = 0; i <= distance; i++)
		{
			image.SetPixel(start + i, name.PositionY, GREEN);
		}
	}

	return other;
}

void Solver::start()
{

	//place the start node on the queue
	nodeQueue.push(NodeMap[StartNode.PositionX][StartNode.PositionY]);
	//run the queue
	checkNode();

	bool foundEnd = NodeMap[EndNode.PositionX][EndNode.PositionY].isChecked;
	if (!foundEnd)
	{
		throw EndNotFoundException();
	}
	//draw the nodes

	Positon temp = EndNode;
	while (true)
	{
		temp = DrawNodes(temp);
		if (temp.PositionX == StartNode.PositionX && temp.PositionY == StartNode.PositionY)
		{
			break;;
		}
	}
	image.SetPixel(StartNode.PositionX, StartNode.PositionY, RED);
	image.SetPixel(EndNode.PositionX, EndNode.PositionY, BLUE);


	image.WriteToFile(getFileName().c_str());
}

Solver::Solver(std::string fileName)
{
	image.ReadFromFile(fileName.c_str());
	fileLocation = fileName;
	FillNodeMap();
	if (EndNode == EMPTY_POSITION)
	{
		throw EndNotFoundException();
	}
	if (StartNode == EMPTY_POSITION)
	{
		throw StartNotFoundException();
	}
}

bool operator==(const RGBApixel & left, const RGBApixel & right)
{
	return left.Alpha == right.Alpha && left.Blue == right.Blue &&
		left.Green == right.Green && left.Red == right.Red;
}

bool operator==(const Positon & left, const Positon & right)
{
	return left.PositionX == right.PositionX && left.PositionY == right.PositionY;
}

bool operator!=(const Positon & left, const Positon & right)
{
	return left.PositionX != right.PositionX || left.PositionY != right.PositionY;
}
