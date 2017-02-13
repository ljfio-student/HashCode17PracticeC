#include "pizza.h"

Pizza::Pizza(Board *b, std::vector<Slice> s) {
  pizza = b;

  slices = s;
  slices_size = slices.size();

  intersections = calc_intersections();
  invalidSlices = calc_invalidSlices();
  notCovered = calc_notCovered();

  isValid = calc_isValid();
  fitness = calc_fitness();
}

bool Pizza::calc_isValid() {
  return
    intersections == 0 &&
    invalidSlices == 0 &&
    notCovered == 0;
}

int Pizza::calc_fitness() {
  return intersections + invalidSlices + notCovered;
}

int Pizza::calc_invalidSlices() {
  std::vector<int> valid;

  int countM, countT;
  bool done = false;

  for (std::vector<Slice>::iterator it = slices.begin(); it != slices.end(); it++) {
    Slice slice = *it;

    done = false;

    countM = 0;
    countT = 0;

    for (int y = slice.fromY; y <= slice.toY && !done; y++) {
      for (int x = slice.fromX; x <= slice.toX && !done; x++) {
        if (pizza->at(y, x) == 'M') {
          countM++;
        } else if (pizza->at(y, x) == 'T') {
          countT++;
        }

        if (countM >= pizza->min_topping && countT >= pizza->min_topping) {
          done = true;
        }
      }
    }

    if (!done) {
      valid.push_back(slice.score);
    }
  }

  return std::accumulate(valid.begin(), valid.end(), 0);
}

int Pizza::calc_intersections() {
  int intersects = 0;

  for (int i = 0; i < slices_size; i++) {
    Slice iSlice = slices.at(i);

    for (int j = i + 1; j < slices_size; j++) {
      Slice jSlice = slices.at(j);

      if (iSlice.intersect(jSlice)) {
        intersects += iSlice.score + jSlice.score;
      }
    }
  }

  return intersects;
}

int Pizza::calc_notCovered() {
  std::vector<int> covered(pizza->size, 1);

  for (std::vector<Slice>::iterator it = slices.begin(); it != slices.end(); it++) {
    Slice slice = *it;

    for (int y = slice.fromY; y <= slice.toY; y++) {
      for (int x = slice.fromX; x <= slice.toX; x++) {
        covered[(y * pizza->columns) + x] = 0;
      }
    }
  }

  return std::accumulate(covered.begin(), covered.end(), 0);
}

bool Pizza::equals(Pizza p) {
  return
    p.slices.size() == slices_size &&
    std::accumulate(slices.begin(), slices.end(), 0,
        [&p](int a, Slice s) {
          return a + std::accumulate(p.slices.begin(), p.slices.end(), 0, [&s](int b, Slice e) {
              return b + (s == e ? 1 : 0);
            });
        }) == slices_size;
}

int Pizza::score() {
  return std::accumulate(slices.begin(), slices.end(), 0, [](int a, Slice s) {
        return a + s.score;
      });
}
