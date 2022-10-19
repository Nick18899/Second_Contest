#include "iostream"

#include "vector"

class BinaryHeap {
 private:
  const static int kMaxSize = 100000;
  std::pair<int, int> heap_[kMaxSize];
  int size_;

 public:
  BinaryHeap() { size_ = 0; }

  int Size() { return size_; }

  static int IndexOfParent(int index) { return (index - 1) / 2; }

  static int IndexOfLeftChild(int index) { return 2 * index + 1; }

  static int IndexOfRightChild(int index) { return 2 * index + 2; }

  int GetMin() { return heap_[0].first; }

  static void Swap(std::pair<int, int>* first_item,
                   std::pair<int, int>* second_item) {
    std::pair<int, int> temp = *first_item;
    *first_item = *second_item;
    *second_item = temp;
  }

  void Insert(std::pair<int, int> value) {
    if (size_ >= kMaxSize) {
      std::cout << "tr" << std::endl;
      return;
    }
    heap_[size_] = value;
    ++size_;
    BinaryHeap::SiftUp(size_ - 1);
  }

  void SiftDown(int index) {
    int index_of_left_child = BinaryHeap::IndexOfLeftChild(index);
    int index_of_right_child = BinaryHeap::IndexOfRightChild(index);
    int index_of_min = index;
    if (index_of_left_child < size_ &&
        heap_[index_of_left_child].first < heap_[index_of_min].first) {
      index_of_min = index_of_left_child;
    }
    if (index_of_right_child < size_ &&
        heap_[index_of_right_child].first < heap_[index_of_min].first) {
      index_of_min = index_of_right_child;
    }
    if (index_of_min != index) {
      std::swap(heap_[index_of_min], heap_[index]);
      SiftDown(index_of_min);
    }
  }

  std::pair<int, int> ExtractMin() {
    std::swap(heap_[0], heap_[size_ - 1]);
    --size_;
    SiftDown(0);
    return heap_[size_];
  }

  void SiftUp(int index) {
    if (index > 0) {
      int parent = IndexOfParent(index);
      if (heap_[index] < heap_[parent]) {
        std::swap(heap_[index], heap_[parent]);
        SiftUp(parent);
      }
    }
  }

  void ChangeValueByKeyId(int id, int index, int delta) {
    if (heap_[index].second == id) {
      heap_[index].first -= delta;
      SiftUp(index);
      SiftDown(0);
    } else {
      int index_of_left_child = BinaryHeap::IndexOfLeftChild(index);
      int index_of_right_child = BinaryHeap::IndexOfRightChild(index);
      if (index_of_left_child <= size_) {
        ChangeValueByKeyId(id, BinaryHeap::IndexOfLeftChild(index), delta);
      }
      if (index_of_right_child <= size_) {
        ChangeValueByKeyId(id, BinaryHeap::IndexOfRightChild(index), delta);
      }
    }
  }
};

std::vector<int> Merge(const std::vector<std::vector<int>>& arrays) {
  BinaryHeap hp;
  std::vector<int> indexes((int)arrays.size(), 0);
  int array_index = 0;
  int size = 0;
  for (auto& array : arrays) {
    if (!array.empty()) {
      hp.Insert({array[0], array_index});
    }
    size += (int)array.size();
    ++array_index;
  }
  std::vector<int> result;
  result.reserve(size);
  while (hp.Size() != 0) {
    std::pair<int, int> val_and_arr_i = hp.ExtractMin();
    result.push_back(val_and_arr_i.first);
    ++indexes[val_and_arr_i.second];
    if (indexes[val_and_arr_i.second] <
        (int)arrays[val_and_arr_i.second].size()) {
      hp.Insert({arrays[val_and_arr_i.second][indexes[val_and_arr_i.second]],
                 val_and_arr_i.second});
    }
  }
  return result;
}

int main() {
  std::vector<std::vector<int>> arrays;
  int n, size;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> size;
    arrays.emplace_back(size);
    for (int j = 0; j < size; ++j) {
      std::cin >> (arrays)[i][j];
    }
  }
  auto result = Merge(arrays);
  for (auto& i : result) {
    std::cout << i << " ";
  }
  return 0;
}
