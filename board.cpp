#include "board.h"

Board::Board(int r, int c, std::string b, int min, int max) {
  rows = r;
  columns = c;
  size = r * c;

  pizza = b;

  min_topping = min;
  max_slice = max;
}

char Board::at(int y, int x) {
  return pizza.at((y * columns) + x);
}
