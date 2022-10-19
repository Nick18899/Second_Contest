#include <iostream>

long long GetByte(long long value, size_t n) { return value >> (8 * n) & 255; }

void CountSort(long long* arr, size_t size_of_arr, size_t num_of_byte) {
  auto* result_array = new long long[size_of_arr];
  size_t count[256];
  for (unsigned long& i : count) {
    i = 0;
  }
  for (size_t i = 0; i < size_of_arr; ++i) {
    ++count[GetByte(arr[i], num_of_byte)];
  }
  for (size_t i = 1; i < 256; ++i) {
    count[i] += count[i - 1];
  }
  for (size_t i = size_of_arr - 1; true; --i) {
    result_array[--count[GetByte(arr[i], num_of_byte)]] = arr[i];
    if (i == 0) {
      break;
    }
  }
  for (size_t i = 0; i < size_of_arr; ++i) {
    arr[i] = result_array[i];
  }
  delete[] result_array;
}

void LSDSort(long long* arr, size_t n) {
  size_t num_of_bytes = sizeof(long long);
  for (size_t degree = 0; degree < num_of_bytes; ++degree) {
    CountSort(arr, n, degree);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n1;
  std::cin >> n1;
  auto* array_for_sorting = new long long[n1];
  for (size_t i = 0; i < n1; ++i) {
    std::cin >> array_for_sorting[i];
  }
  LSDSort(array_for_sorting, n1);
  for (size_t i = 0; i < n1; ++i) {
    std::printf("%lld %c", array_for_sorting[i], '\n');
  }
  delete[] array_for_sorting;
  return 0;
}
