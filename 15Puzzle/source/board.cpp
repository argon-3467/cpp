#include "../headers/board.h"

#include "../headers/direction.h"
#include "../headers/point.h"

void Board::printEmptyLines(int count) {
  for (int i = 0; i < count; ++i) std::cout << '\n';
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
  // Before drawing always print some empty lines
  // so that only one board appears at a time
  // and it's always shown at the bottom of the window
  // because console window scrolls automatically when there is no
  // enough space.
  Board::printEmptyLines(g_consoleLines);

  for (int y = 0; y < board.SIZE; ++y) {
    for (int x = 0; x < board.SIZE; ++x) out << board.m_board[y][x];
    out << '\n';
  }
  return out;
}

Point Board::getEmptyTile() const {
  for (int x = 0; x < SIZE; ++x) {
    for (int y = 0; y < SIZE; y++) {
      if (m_board[x][y].isEmpty()) return Point{x, y};
    }
  }
  assert(false && "There is no empty tile ... should never happen");
  Point{-1, -1};
}

bool Board::isOnBoard(Point p) const {
  return p.m_x >= 0 && p.m_x < 4 && p.m_y >= 0 && p.m_y < 4;
}

void Board::swapTile(Point p1, Point p2) {
  // ep is emptyTilePoint and ap is a Point to swap with
  std::swap(m_board[p1.m_x][p1.m_y], m_board[p2.m_x][p2.m_y]);
}

bool Board::slideTile(Direction dir) {
  Point emptyTilePoint{getEmptyTile()};
  Point adjPoint{emptyTilePoint.getAdjPoint(-dir)};
  if (isOnBoard(adjPoint)) {
    swapTile(emptyTilePoint, adjPoint);
    return true;
  }
  return false;
}

void Board::randomize(int n) {
  for (int i = 0; i < n; ++i) {
    Direction randDir = Direction::getRandDir();
    slideTile(randDir);
  }
}
