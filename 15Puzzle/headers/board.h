#ifndef BOARD_14_49_22_08_2023_H
#define BOARD_14_49_22_08_2023_H

#include "point.h"
#include "tile.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{25};

class Board {
 private:
  static constexpr int SIZE = 4;
  Tile m_board[SIZE][SIZE]{{Tile{1}, Tile{2}, Tile{3}, Tile{4}},
                           {Tile{5}, Tile{6}, Tile{7}, Tile{8}},
                           {Tile{9}, Tile{10}, Tile{11}, Tile{12}},
                           {Tile{13}, Tile{14}, Tile{15}, Tile{0}}};

 public:
  Board() = default;

  // Print a given number of Empty lines
  static void printEmptyLines(int);
  // Returns a Point representing empty tile
  Point getEmptyTile() const;
  // Returns true if Point is Valid i.e on a 4x4 board
  bool isOnBoard(Point) const;
  // Slide a tile to fill the empty file in the given direction
  bool slideTile(Direction);
  // Swap contents of two tiles
  void swapTile(Point, Point);
  // Randomize the board a given no. of times
  void randomize(int n = 300);

  friend std::ostream& operator<<(std::ostream& stream, const Board& board);
};

#endif
