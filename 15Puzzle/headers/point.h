#ifndef POINT_16_24_22_08_2023_H
#define POINT_16_24_22_08_2023_H
#include "direction.h"

class Point {
 public:
  int m_x{};
  int m_y{};
  Point(int x = 0, int y = 0) : m_x{x}, m_y{y} {}
  // Returns adjecent point in the given direction
  Point getAdjPoint(const Direction dir) {
    switch (dir.getDir()) {
      // up => row decrease, column same
      case Direction::up:
        return Point{m_x - 1, m_y};
      // down => row increase, column same
      case Direction::down:
        return Point{m_x + 1, m_y};
      // left => row same, column decrease
      case Direction::left:
        return Point{m_x, m_y - 1};
      // right => row same, column increase
      case Direction::right:
        return Point{m_x, m_y + 1};
    }

    return *this;
  }
  // True if both x and y coordinates are equal
  friend bool operator==(const Point& p1, const Point& p2) {
    return p1.m_x == p2.m_x && p1.m_y == p2.m_y;
  }
  // True if Points are unequal
  friend bool operator!=(const Point& p1, const Point& p2) {
    return !(p1 == p2);
  }
};

#endif
