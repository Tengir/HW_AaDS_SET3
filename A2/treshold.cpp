#include "ArrayGenerator.h"
#include "SortTester.h"
#include "MergeSort.h"
#include <iostream>
#include <cstdint>

int main() {
  const int max_size = 10000;
  const int step = 100;
  const int range = 6000;
  const int repetitions = 5;
  const std::vector<int> thresholds = {5, 30, 60, 100, 200};

  ArrayGenerator generator;
  std::vector<int> random_array = generator.GenerateRandomArray(max_size, range);
  std::vector<int> reversed_array = generator.GenerateReversedArray(max_size);
  std::vector<int> nearly_sorted_array = generator.GenerateNearlySortedArray(max_size, max_size / 10);

  for (int size = 500; size <= max_size; size += step) {
    std::vector<int> random_sub(random_array.begin(), random_array.begin() + size);
    std::vector<int> reversed_sub(reversed_array.begin(), reversed_array.begin() + size);
    std::vector<int> nearly_sorted_sub(nearly_sorted_array.begin(), nearly_sorted_array.begin() + size);

    for (int threshold : thresholds) {
      int64_t time_hybrid_random = 0;
      int64_t time_hybrid_reversed = 0;
      int64_t time_hybrid_nearly_sorted = 0;

      for (int i = 0; i < repetitions; ++i) {
        time_hybrid_random += SortTester::MeasureSortTime(random_sub, [threshold](std::vector<int>& arr) {
          MergeSort::HybridMergeSort(arr, 0, arr.size() - 1, threshold);
        });

        time_hybrid_reversed += SortTester::MeasureSortTime(reversed_sub, [threshold](std::vector<int>& arr) {
          MergeSort::HybridMergeSort(arr, 0, arr.size() - 1, threshold);
        });

        time_hybrid_nearly_sorted += SortTester::MeasureSortTime(nearly_sorted_sub, [threshold](std::vector<int>& arr) {
          MergeSort::HybridMergeSort(arr, 0, arr.size() - 1, threshold);
        });
      }

      std::cout << size << " " << threshold << " "
                << (time_hybrid_random / repetitions) << " "
                << (time_hybrid_reversed / repetitions) << " "
                << (time_hybrid_nearly_sorted / repetitions) << std::endl;
    }
  }

  return 0;
}
