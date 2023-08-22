#ifndef TILE_14_28_22_08_2023_H
#define TILE_14_28_22_08_2023_H

#include <iostream>
class Tile {
 private:
  // 0 means empty otherwise 1 to 15
  int m_value{};

 public:
  explicit Tile(int);
  // Returns value of the Tile obj
  int getNum() const;
  // Returns true if Tile has a value of 0
  bool isEmpty() const;
  // Prints The value of Tile or space if Value is 0
  friend std::ostream& operator<<(std::ostream&, const Tile);
};
#endif
