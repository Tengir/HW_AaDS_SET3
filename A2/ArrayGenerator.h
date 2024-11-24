#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H

#include <vector>
#include <algorithm>
#include <random>

class ArrayGenerator {
 public:
  static std::vector<int> GenerateRandomArray(int size, int range) {
    std::vector<int> arr(size);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, range);
    std::generate(arr.begin(), arr.end(), [&]() { return dist(rng); });
    return arr;
  }

  static std::vector<int> GenerateReversedArray(int size) {
    std::vector<int> arr(size);
    std::iota(arr.rbegin(), arr.rend(), 1);
    return arr;
  }

  static std::vector<int> GenerateNearlySortedArray(int size, int swaps) {
    std::vector<int> arr(size);
    std::iota(arr.begin(), arr.end(), 1);
    std::mt19937 rng(std::random_device{}());
    for (int i = 0; i < swaps; ++i) {
      int idx1 = rng() % size;
      int idx2 = rng() % size;
      std::swap(arr[idx1], arr[idx2]);
    }
    return arr;
  }
};

#endif
