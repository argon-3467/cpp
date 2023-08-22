#include "../headers/tile.h"

#include <cassert>
#include <iomanip>
#include <iostream>

Tile::Tile(int value = 0) : m_value{value} { assert(value >= 0 && value < 16); }

int Tile::getNum() const { return m_value; }

bool Tile::isEmpty() const { return !m_value; }

std::ostream& operator<<(std::ostream& out, const Tile t) {
  if (t.m_value)
    out << std::setw(3) << t.m_value << " ";
  else
    out << "    ";
  return out;
}
