#include <string>

#ifndef BOARD_H
#define BOARD_H

class Board {
  std::string pizza;
public:
  Board(int, int, std::string, int, int);
  int size, rows, columns, min_topping, max_slice;
  char at(int, int);
};

#endif
