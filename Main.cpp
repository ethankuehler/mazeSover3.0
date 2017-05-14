// mazeSolver3.cpp : Defines the entry point for the console application.
//

#include <ctime>
#include "Solver.h"

int main(const int argc, const char* argv[]) {
  clock_t start = clock();

  for (size_t i = 1; i < argc; ++i) {
    std::string file = argv[i];
    try {
      Solver s(file);
      s.start();
    } catch (const std::exception& e) {
      std::cout << "the maze " << argv[i] << ": " << e.what() << '\n';
    }
  }

  double duration = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
  std::cout << "total time: " << duration << '\n';
}
