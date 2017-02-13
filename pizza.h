#include <vector>
#include <numeric>
#include <functional>
#include "slice.h"
#include "board.h"

#ifndef PIZZA_H
#define PIZZA_H

class Pizza {
  int slices_size, intersections, invalidSlices, notCovered;
  Board *pizza;

  int calc_intersections();
  int calc_invalidSlices();
  int calc_notCovered();
  int calc_fitness();

  bool calc_isValid();

public:
  std::vector<Slice> slices;
  bool isValid;
  int fitness;

  Pizza(Board*, std::vector<Slice>);
  std::string output();
  int score();
  bool equals(Pizza);
};

#endif
