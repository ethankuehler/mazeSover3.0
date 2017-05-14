#include "FileName.h"

std::string getFileName() {
  ++id;
  std::ostringstream oss;
  oss << "output" << id << ".bmp";
  return oss.str();
}
