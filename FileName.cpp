#include "FileName.h"
#include <sstream>
std::string getFileName() {
  ++id;
  std::string output =  "output" + std::to_string(id)  + ".bmp";
  return output;
}
