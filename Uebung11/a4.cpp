#include <vector>
#include <iostream>

template <typename T>
class PqElement {
  public:
  T value;
  int key;
  PqElement(T, int);
};

template <typename T>
PqElement<T>::PqElement(T value, int key) {
  this->value = value;
  this->key = key;
}

template <typename T>
class PriorityQueue {
  private:
  std::vector<PqElement<T>> elements;
  void InsertAtCorrectPosition(PqElement<T>);

  public:
  void Insert(T, int);
  PqElement<T> GetMin();
  PqElement<T> ExtractMin();
  void DecreaseKey(unsigned int, int);
  void Print();
};

template <typename T>
void PriorityQueue<T>::InsertAtCorrectPosition(PqElement<T> element) {
  if (elements.empty()) {
    elements.push_back(element);
    return;
  }
  
  for (int i = 0; i < elements.size(); i++) {
    PqElement<T> element_to_compare = elements.at(i);
    if (element_to_compare.key <= element.key) {
      continue;
    }
    elements.insert(elements.begin() + i, element);
    return;
  }

  elements.push_back(element);
}

template <typename T>
void PriorityQueue<T>::Insert(T value, int key) {
  PqElement<T> element(value, key);
  InsertAtCorrectPosition(element);
}

template <typename T>
PqElement<T> PriorityQueue<T>::GetMin() {
  return elements.front();  
}

template <typename T>
PqElement<T> PriorityQueue<T>::ExtractMin() {
  PqElement<T> element = GetMin();
  elements.erase(elements.begin());
  return element;
}

template <typename T>
void PriorityQueue<T>::DecreaseKey(unsigned int position, int key) {
  PqElement<T> element = elements.at(position);
  if (element.key <= key) {
    return;
  }
  element.key = key;
  elements.erase(elements.begin() + position);
  InsertAtCorrectPosition(element);
}

template <typename T>
void PriorityQueue<T>::Print() {
  for (unsigned int i = 0; i < elements.size(); i++) {
    PqElement<T> element = elements.at(i);
    std::cout << element.value << " [" << element.key << "]";
    if (i == elements.size() - 1) {
      std::cout << std::endl;
      return;
    }
    std::cout << " | ";
  }
}

int main() {
  PriorityQueue<int> PQ;
  PQ.Insert(6, 2);
  PQ.Insert(2, 3);
  PQ.Insert(1, 2);
  PQ.Insert(5, 7);
  PQ.Insert(1, 0);
  PQ.Print();

  PqElement<int> elem = PQ.GetMin();
  std::cout << elem.value << " [" << elem.key << "]" << std::endl;

  PQ.DecreaseKey(4, 9);
  PQ.DecreaseKey(3, 0);
  PQ.Print();

  elem = PQ.ExtractMin();
  std::cout << elem.value << " [" << elem.key << "]" << std::endl;
  elem = PQ.ExtractMin();
  std::cout << elem.value << " [" << elem.key << "]" << std::endl;
  elem = PQ.ExtractMin();
  std::cout << elem.value << " [" << elem.key << "]" << std::endl;
  elem = PQ.ExtractMin();
  std::cout << elem.value << " [" << elem.key << "]" << std::endl;
  elem = PQ.ExtractMin();
  std::cout << elem.value << " [" << elem.key << "]" << std::endl;

  PQ.Print();
  PQ.Insert(6, 9);
  PQ.Insert(4, 2);
  PQ.Print();
}