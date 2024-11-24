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

  ArrayGenerator generator;
  std::vector<int> random_array = generator.GenerateRandomArray(max_size, range);
  std::vector<int> reversed_array = generator.GenerateReversedArray(max_size);
  std::vector<int> nearly_sorted_array = generator.GenerateNearlySortedArray(max_size, max_size / 10);

  for (int size = 500; size <= max_size; size += step) {
    std::vector<int> random_sub(random_array.begin(), random_array.begin() + size);
    std::vector<int> reversed_sub(reversed_array.begin(), reversed_array.begin() + size);
    std::vector<int> nearly_sorted_sub(nearly_sorted_array.begin(), nearly_sorted_array.begin() + size);

    int64_t time_merge_random = 0;
    int64_t time_hybrid_random = 0;
    int64_t time_merge_reversed = 0;
    int64_t time_hybrid_reversed = 0;
    int64_t time_merge_nearly_sorted = 0;
    int64_t time_hybrid_nearly_sorted = 0;

    for (int i = 0; i < repetitions; ++i) {
      time_merge_random += SortTester::MeasureSortTime(random_sub, [](std::vector<int>& arr) {
        MergeSort::ClassicMergeSort(arr, 0, arr.size() - 1);
      });
      time_hybrid_random += SortTester::MeasureSortTime(random_sub, [](std::vector<int>& arr) {
        MergeSort::HybridMergeSort(arr, 0, arr.size() - 1, 30);
      });

      time_merge_reversed += SortTester::MeasureSortTime(reversed_sub, [](std::vector<int>& arr) {
        MergeSort::ClassicMergeSort(arr, 0, arr.size() - 1);
      });
      time_hybrid_reversed += SortTester::MeasureSortTime(reversed_sub, [](std::vector<int>& arr) {
        MergeSort::HybridMergeSort(arr, 0, arr.size() - 1, 30);
      });

      time_merge_nearly_sorted += SortTester::MeasureSortTime(nearly_sorted_sub, [](std::vector<int>& arr) {
        MergeSort::ClassicMergeSort(arr, 0, arr.size() - 1);
      });
      time_hybrid_nearly_sorted += SortTester::MeasureSortTime(nearly_sorted_sub, [](std::vector<int>& arr) {
        MergeSort::HybridMergeSort(arr, 0, arr.size() - 1, 30);
      });
    }

    std::cout << size << " "
              << (time_merge_random / repetitions) << " " << (time_hybrid_random / repetitions) << " "
              << (time_merge_reversed / repetitions) << " " << (time_hybrid_reversed  / repetitions) << " "
              << (time_merge_nearly_sorted / repetitions) << " " << (time_hybrid_nearly_sorted / repetitions) << std::endl;
  }

  return 0;
}
