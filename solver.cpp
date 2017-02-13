#include <utility>
#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <unordered_set>

#include "slice.h"
#include "pizza.h"
#include "board.h"

namespace std {
  template <typename T, typename U> struct hash<std::pair<T, U>> {
    std::size_t operator()(const std::pair<T, U>& x) {
      return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
    }
  };

  template <> struct hash<Slice> {
    std::size_t operator()(const Slice& x) {
      return x.fromX + x.fromY + x.toX + x.toY;
    }
  };
}

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 rng(seed);

std::vector<int> random_range(int min, int max, int amount) {
  std::vector<int> range(amount);

  std::uniform_int_distribution<int> distr(min, max);
  std::generate(range.begin(), range.end(), [&](){ return distr(rng); });

  return range;
}

std::unordered_set<std::pair<int, int>> get_factors(int rows, int columns, int min_size, int max_size) {
  std::unordered_set<std::pair<int, int>> factors;

  for (int y = 1; y <= columns; y++) {
    for (int x = 1; x <= rows; x++) {
      int size = (x * y);

      if (size >= min_size && size <= max_size) {
        std::pair<int, int> factor(x, y);
        factors.insert(factor);
      }
    }
  }

  return factors;
}

std::vector<Slice> get_slices(Board pizza, std::unordered_set<std::pair<int, int>> factors) {
  std::unordered_set<Slice> inner, outer;
  std::vector<Slice> slices;

  bool options[] = { true, false };

  for (auto factor = factors.begin(); factor != factors.end(); ++factor) {
    for (int b = 0; b < 2; b++) {
      bool rotate = options[b];

      inner.clear();

      int xf = (rotate ? factor->second : factor->first) - 1;
      int yf = (rotate ? factor->first : factor->second) - 1;

      for (int y = 0; (y + yf) < pizza.rows; y++) {
        for (int x = 0; (x + xf) < pizza.columns; x++) {
          Slice s(x, y, *factor, rotate);
          inner.insert(s);
        }
      }

      outer.insert(inner.begin(), inner.end());
    }
  }

  slices.insert(slices.begin(), outer.begin(), outer.end());

  return slices;
}

int main () {
  std::pair<int, int> factor(2, 1);
  std::vector<Slice> slices;

  std::string pizza = "TMMT";

  Slice one(0, 0, factor, false);
  Slice two(0, 0, factor, false);

  slices.push_back(one);
  slices.push_back(two);

  auto board = new Board(200, 250, pizza, 4, 12);
  Pizza p(board, slices);

  auto table = random_range(0, 63, 8);
  auto fs = get_factors(200, 250, 4, 12);

  //for (auto it = fs.begin(); it != fs.end(); ++it) {
  //  std::cout << it->first << " " << it->second << std::endl;
  //}

  std::cout << fs.size() << std::endl;

  auto ss = get_slices(*board, fs);
//  std::copy(fs.begin(), fs.end(), std::ostream_iterator<int>(std::cout, " "));

  std::cout << ss.size() << std::endl;

  //for (auto it = ss.begin(); it != ss.end(); ++it) {
  //  std::cout << it->output() << std::endl;
  //}

//  std::cout << one.output() << two.output() << std::endl;
//  std::cout << (p.isValid ? "true " : "false ") << p.fitness << std::endl;
}
