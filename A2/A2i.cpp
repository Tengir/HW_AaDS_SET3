#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

class MergeSort {
 public:
  static void ClassicMergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
      return;
}
    int mid = left + (right - left) / 2;
    ClassicMergeSort(arr, left, mid);
    ClassicMergeSort(arr, mid + 1, right);
    Merge(arr, left, mid, right);
  }

  static void HybridMergeSort(std::vector<int>& arr, int left, int right, int threshold) {
    if (right - left + 1 <= threshold) {
      InsertionSort(arr, left, right);
      return;
    }
    int mid = left + (right - left) / 2;
    HybridMergeSort(arr, left, mid, threshold);
    HybridMergeSort(arr, mid + 1, right, threshold);
    Merge(arr, left, mid, right);
  }

 private:
  static void Merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
      if (arr[i] <= arr[j]) {
        temp[k++] = arr[i++];
      } else {
        temp[k++] = arr[j++];
      }
    }

    while (i <= mid) {
      temp[k++] = arr[i++];
    }
    while (j <= right) {
      temp[k++] = arr[j++];
    }

    for (int r = 0; r < temp.size(); ++r) {
      arr[left + r] = temp[r];
    }
  }

  static void InsertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
      int key = arr[i];
      int j = i - 1;
      while (j >= left && arr[j] > key) {
        arr[j + 1] = arr[j];
        --j;
      }
      arr[j + 1] = key;
    }
  }
};

#endif
