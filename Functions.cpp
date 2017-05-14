#include "Solver.h"
#include "string"
extern "C" {
  int START_SOLVER(char fileLocation[]) {
    std::string file = fileLocation;
    try {
      Solver s(file);
      s.start();
    } catch (const std::exception &e) {
      return 1;
    }
    return 0;
  }
}
