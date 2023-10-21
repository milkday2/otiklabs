#include <iostream>
#include "filestats.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "command should include a file name\n";
    return 0;
  }
  std::string path(argv[1]);
  task1(path);
  return 0;
}
