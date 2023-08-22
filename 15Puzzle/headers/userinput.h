#ifndef USERINPUT_15_24_22_08_2023_H
#define USERINPUT_15_24_22_08_2023_H

#include <cassert>
#include <iostream>
#include <limits>

#include "direction.h"

namespace UserInput {
// True if command is one of 'w' || 'a' || 's' || 'd' || 'q'
bool isValidCommand(char ch) {
  return ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'q';
}
// Ignores rest of the buffer input upto \n after taking a char as input
void ignoreLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Takes the first char as Input and ignore rest upto newline
char getCharacter() {
  char operation{};
  std::cin >> operation;
  ignoreLine();  // remove any extraneous input
  return operation;
}
// keeps asking for user Input until a valid command is entered
char getCommandFromUser() {
  char ch{};
  while (!isValidCommand(ch)) ch = getCharacter();

  return ch;
}
// Returns Direction of a give valid command
Direction charToDir(char ch) {
  switch (ch) {
    case 'w':
      return Direction{Direction::up};
    case 's':
      return Direction{Direction::down};
    case 'a':
      return Direction{Direction::left};
    case 'd':
      return Direction{Direction::right};

    default:
      assert(false && "??? ... should never happen");
  }
}

}  // namespace UserInput

#endif
