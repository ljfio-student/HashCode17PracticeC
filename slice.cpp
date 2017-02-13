#include "slice.h"

Slice::Slice(int x, int y, std::pair<int, int> factor, bool rotate) {
  fromX = x;
  fromY = y;

  toX = x + (rotate ? factor.second : factor.first) - 1;
  toY = y + (rotate ? factor.first : factor.second) - 1;

  score = factor.first * factor.second;
}

bool Slice::intersect(Slice s) {
  return
    s.fromX <= toX &&
    s.toX >= fromX &&
    s.fromY <= toY &&
    s.toY >= fromY;
}

bool Slice::operator==(const Slice& s) const {
  return
    fromX == s.fromX &&
    fromY == s.fromY &&
    toX == s.toX &&
    toY == s.toY;
}

std::string Slice::output() {
  return
    std::to_string(fromY) + " " +
    std::to_string(fromX) + " " +
    std::to_string(toY) + " " +
    std::to_string(toX);
}
