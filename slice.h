#include <utility>
#include <string>

#ifndef SLICE_H
#define SLICE_H

class Slice {
 public:
  int fromX, toX, fromY, toY, score;

  Slice(int, int, std::pair<int, int>, bool);
  bool intersect(Slice);
  std::string output();

  bool operator==(const Slice&) const;
};

#endif
