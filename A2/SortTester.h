#ifndef SORTTESTER_H
#define SORTTESTER_H

#include <vector>
#include <chrono>
#include <functional>
#include <iostream>
#include <algorithm>
#include <cstdint>

class SortTester {
 public:
  static int64_t MeasureSortTime(std::vector<int> arr, std::function<void(std::vector<int>&)> sort_function) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_function(arr);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
  }
};

#endif
