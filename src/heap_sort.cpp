#include "assignment/heap_sort.hpp"

#include <utility>  // swap
#include <cassert>  // assert

namespace assignment {

  void HeapSort::Sort(std::vector<int>& arr) const {

    // строим двоичную кучу ... BuildMaxHeap ...
    BuildMaxHeap(arr);
    // обходим элементы кучи с конца до корня (не включительно)
    for (int index = static_cast<int>(arr.size()) - 1; index > 0; index--) {
      // обмениваем местами корень (максимальный элемент) и последний элемент кучи ... std::swap ...
      std::swap(arr[0], arr[index]);

      // спускаем новый корневой узел вниз ... Heapify ...
      Heapify(arr, index, 0);
    }
  }

  void HeapSort::BuildMaxHeap(std::vector<int>& arr) {

    // Комментарии:
    // - построение начинается с последнего не листового узла (листовые узлы спускать не нужно - лишняя операция)
    // - индекс последнего не листового узла = parent (size - 1) = ((size - 1) - 1) / 2 = size / 2 - 1
    // - индекс идет до корня (включительно)

    const int size = static_cast<int>(arr.size());

    int start = size / 2 - 1;
    for (int i = start; i >= 0; i--) {
      Heapify(arr,size,i);
    }
  }

  void HeapSort::Heapify(std::vector<int>& arr, int heap_size, int index) {
    assert(heap_size >= 0 && heap_size <= arr.size() && index >= 0 && index < heap_size);

    // максимальный элемент устанавливаем в значение текущего индекса
    for (int largest = index; largest < heap_size; ){
      // вычисляем индексы потомков для текущего элемента
      const int left_child = LeftChild(index);
      const int right_child = RightChild(index);

      // поиск наибольшего элемента среди текущего элемента и его потомков ...
      if (left_child < heap_size && arr[left_child]>arr[largest]) {
        largest = left_child;
      }
      else if (right_child < heap_size && arr[right_child]>arr[largest]) {
        largest = right_child;
      }

      // если текущий элемент больше своих потомков, то он находится на правильном месте (свойство макс. кучи)
      if (largest == index) {
        return;  // завершаем спуск
      }

      // обмениваем местами текущий элемент с его потомком ... std::swap ...
      std::swap(arr[index], arr[largest]);

      // продолжаем спуск c нового места (после операции обмена местами)
      index = largest;
    }
  }

  int HeapSort::Parent(int index) {
    assert(index >= 0);
    return (index - 1) / 2;
  }

  int HeapSort::LeftChild(int index) {
    assert(index >= 0);
    return 2 * index + 1;
  }

  int HeapSort::RightChild(int index) {
    assert(index >= 0);
    return 2 * index + 2;
  }

}  // namespace assignment
