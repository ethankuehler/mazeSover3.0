#include "FileName.h"
<<<<<<< HEAD
#include <sstream>

std::string getFileName()
{
  ++id;
  std::ostringstream oss;
  oss << "output" << id << ".bmp";
  return oss.str();
=======

std::string getFileName() {
  ++id;
  std::ostringstream oss;
  oss << "output" << id << ".bmp";
  return oss.str();
>>>>>>> origin/LIB
}
