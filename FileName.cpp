#include "FileName.h"
#include <sstream>

std::string getFileName()
{
	++id;
	std::ostringstream oss;
	oss << "output" << id << ".bmp";
	return oss.str();
}