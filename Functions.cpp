#include "Solver.h"
#include <string>

extern "C" {
int START_SOLVER(char fileLocation[]) {
  std::string file = fileLocation;
  try {
    Solver s(file);
    s.start();
  } catch (const StartNotFoundException& e) {
    return 1;
  } catch (const EndNotFoundException& e) {
    return 2;
  } catch (const NoPathToEnd& e) {
    return 3;
  } catch (...) {
    return 4;
  }
  return 0;
}
}
