#ifndef DIRECTION_15_48_22_08_2023_H
#define DIRECTION_15_48_22_08_2023_H

#include <cassert>
#include <iostream>

#include "random.h"

class Direction {
 public:
  enum Dir {
    up,
    down,
    left,
    right,

    max_directions,
  };

 private:
  Dir m_dir{};

 public:
  Direction(Dir dir) : m_dir{dir} {}
  Dir getDir() const { return m_dir; }
  // Reverses Direction
  Direction operator-() const {
    switch (m_dir) {
      case up:
        return Direction{down};
      case down:
        return Direction{up};
      case left:
        return Direction{right};
      case right:
        return Direction{left};

      default:
        assert(false && "??? ... should never happen");
    }
  }
  // Print Direction
  friend std::ostream& operator<<(std::ostream& out, Direction dir) {
    switch (dir.getDir()) {
      case up:
        return (out << "up");
      case down:
        return (out << "down");
      case left:
        return (out << "left");
      case right:
        return (out << "right");

      default:
        return (out << "???");
    }
  }
  // Returns a Random Direction from up, down, left and right
  static Direction getRandDir() {
    Dir random{static_cast<Dir>(Random::get(0, Dir::max_directions - 1))};
    return Direction{random};
  }
};

#endif
