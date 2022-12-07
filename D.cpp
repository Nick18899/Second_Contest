#include "iostream"

#include "cmath"

#include "vector"

class BinaryHeapMax {
 private:
  const static unsigned int kMaxSize = 2000;
  unsigned int heap_[kMaxSize];
  unsigned int size_;

 public:
  BinaryHeapMax() {
    size_ = 0;
    heap_[size_] = 0;
  }

  unsigned int Size() { return size_; }

  void Clear() { size_ = 0; }

  static unsigned int IndexOfParent(unsigned int index) {
    return (index - 1) / 2;
  }

  static unsigned int IndexOfLeftChild(unsigned int index) {
    return 2 * index + 1;
  }

  static unsigned int IndexOfRightChild(unsigned int index) {
    return 2 * index + 2;
  }

  unsigned int GetMax() { return heap_[0]; }

  static void Swap(std::pair<unsigned int, unsigned int>* first_item,
                   std::pair<unsigned int, unsigned int>* second_item) {
    std::pair<unsigned int, unsigned int> temp = *first_item;
    *first_item = *second_item;
    *second_item = temp;
  }

  void Insert(unsigned int value) {
    if (size_ >= kMaxSize) {
      std::cout << "error" << std::endl;
      return;
    }
    heap_[size_] = value;
    ++size_;
    BinaryHeapMax::SiftUp(size_ - 1);
  }

  void SiftDown(unsigned int index) {
    if (size_ > 1) {
      unsigned int index_of_left_child = BinaryHeapMax::IndexOfLeftChild(index);
      unsigned int index_of_right_child =
          BinaryHeapMax::IndexOfRightChild(index);
      unsigned int index_of_max = index;
      if (index_of_left_child < size_ &&
          heap_[index_of_left_child] > heap_[index_of_max]) {
        index_of_max = index_of_left_child;
      }
      if (index_of_right_child < size_ &&
          heap_[index_of_right_child] > heap_[index_of_max]) {
        index_of_max = index_of_right_child;
      }
      if (index_of_max != index) {
        std::swap(heap_[index_of_max], heap_[index]);
        SiftDown(index_of_max);
      }
    }
  }

  unsigned int ExtractMax() {
    std::swap(heap_[0], heap_[size_ - 1]);
    --size_;
    SiftDown(0);
    return heap_[size_];
  }

  void SiftUp(unsigned int index) {
    if (size_ > 1) {
      if (index > 0) {
        unsigned int parent = IndexOfParent(index);
        if (heap_[index] > heap_[parent]) {
          std::swap(heap_[index], heap_[parent]);
          SiftUp(parent);
        }
      }
    }
  }
};

int main() {
  unsigned int n, k, a0, x, y;
  std::cin >> n >> k;
  std::cin >> a0 >> x >> y;
  BinaryHeapMax priority_queue;
  unsigned int last_element = a0;
  ++n;
  for (unsigned int i = 1; i < n; ++i) {
    last_element = (x * last_element + y) % (unsigned int)pow(2, 30);
    if (priority_queue.Size() < k) {
      priority_queue.Insert(last_element);
    } else if (priority_queue.GetMax() > last_element) {
      priority_queue.ExtractMax();
      priority_queue.Insert(last_element);
    }
  }
  std::vector<unsigned int> result;
  while (priority_queue.Size() != 0) {
    result.push_back(priority_queue.ExtractMax());
  }
  for (int i = (int)result.size() - 1; i >= 0; --i) {
    std::cout << result[i] << " ";
  }
  return 0;
}
