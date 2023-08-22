#include <iostream>
#include <limits>

#include "headers/board.h"
#include "headers/direction.h"
#include "headers/point.h"
#include "headers/tile.h"
#include "headers/userinput.h"

int main() {
  Board board{};
  board.randomize(300);
  std::cout << board;
  while (true) {
    std::cout << "Enter a command: ";
    char ch{UserInput::getCommandFromUser()};

    // Handle non-direction commands
    if (ch == 'q') {
      std::cout << "\n\nBye!\n\n";
      return 0;
    }

    // Handle direction commands
    Direction dir{UserInput::charToDir(ch)};

    bool userMoved{board.slideTile(dir)};
    if (userMoved) std::cout << board;
  }

  return 0;
}
