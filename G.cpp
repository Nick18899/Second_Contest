#include <iostream>

long Partition(long* arr_of_elements, long left, long right) {
  long l = left;
  long r = right;
  long mid = arr_of_elements[(left + right) / 2];
  while (l <= r) {
    while (arr_of_elements[r] > mid) {
      --r;
    }
    while (arr_of_elements[l] < mid) {
      ++l;
    }
    if (l >= r) {
      break;
    }
    std::swap(arr_of_elements[l], arr_of_elements[r]);
    ++l;
    --r;
  }
  return r;
}

void QuickSort(long* array_of_elements, int left, int right) {
  if (right > left) {
    int mid = Partition(array_of_elements, left, right);
    QuickSort(array_of_elements, left, mid);
    QuickSort(array_of_elements, mid + 1, right);
  }
}

int main() {
  int n, x;
  std::cin >> n;
  long* array_for_sorting = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    array_for_sorting[i] = x;
  }
  QuickSort(array_for_sorting, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << array_for_sorting[i] << " ";
  }
  delete[] array_for_sorting;
  return 0;
}
