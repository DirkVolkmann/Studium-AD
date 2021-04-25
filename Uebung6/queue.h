#ifndef _QUEUE_H
#define _QUEUE_H 1

#include <iostream>

template <typename T>
class QElement {
 public:
  T value;
  QElement<T> *next;
};

template <typename T>
class Queue {
 private:
  QElement<T> *head_;
  QElement<T> *tail_;
  QElement<T> *QuickSortR_(QElement<T> *, QElement<T> *);
  QElement<T> *GetTail_(QElement<T> *);
  QElement<T> *Partition_(QElement<T> *, QElement<T> *, QElement<T> *&,
                          QElement<T> *&);

 public:
  Queue();
  ~Queue();
  void Append(T);
  void DeleteList();
  void DeleteValue(T);
  void Print();
  void QuickSort();
};

template <typename T>
Queue<T>::Queue() {
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
  this->DeleteList();
}

template <typename T>
void Queue<T>::Append(T value_to_apptail) {
  QElement<T> *element = new QElement<T>;
  element->value = value_to_apptail;
  element->next = nullptr;

  if (tail_ == nullptr) {
    head_ = element;
    tail_ = element;
  } else {
    tail_->next = element;
    tail_ = element;
  }
}

template <typename T>
void Queue<T>::DeleteList() {
  QElement<T> *currentent = head_;
  QElement<T> *next = nullptr;
  while (currentent != nullptr) {
    next = currentent->next;
    delete currentent;
    currentent = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
void Queue<T>::DeleteValue(T value_to_delete) {
  QElement<T> *currentent = head_, *previousious = nullptr;

  while (currentent != nullptr) {
    if (currentent->value == value_to_delete) {
      if (previousious == nullptr)
        head_ = currentent->next;
      else
        previousious->next = currentent->next;

      if (currentent == tail_) tail_ = previousious;

      QElement<T> *delete_this = currentent;
      currentent = currentent->next;
      delete delete_this;
    } else {
      previousious = currentent;
      currentent = currentent->next;
    }
  }
}

template <typename T>
void Queue<T>::Print() {
  QElement<T> *currentent = head_;
  while (currentent != nullptr) {
    std::cout << currentent->value << " ";
    currentent = currentent->next;
  }
  std::cout << std::endl;
}

template <typename T>
void Queue<T>::QuickSort() {
  QElement<T> *head_new = QuickSortR_(head_, tail_);
  head_ = head_new;
  tail_ = GetTail_(head_);
}

template <typename T>
QElement<T> *Queue<T>::QuickSortR_(QElement<T> *head, QElement<T> *tail) {
  if (head == nullptr || head == tail) return head;

  QElement<T> *head_new = nullptr, *tail_new = nullptr;

  QElement<T> *pivot = Partition_(head, tail, head_new, tail_new);

  if (head_new != pivot) {
    QElement<T> *temp = head_new;
    while (temp->next != pivot) temp = temp->next;
    temp->next = nullptr;

    head_new = QuickSortR_(head_new, temp);

    temp = GetTail_(head_new);
    temp->next = pivot;
  }

  pivot->next = QuickSortR_(pivot->next, tail_new);

  return head_new;
}

template <typename T>
QElement<T> *Queue<T>::Partition_(QElement<T> *head, QElement<T> *tail,
                                  QElement<T> *&head_new,
                                  QElement<T> *&tail_new) {
  QElement<T> *pivot = tail, *previous = nullptr, *current = head;
  tail = pivot;

  while (current != pivot) {
    if (current->value < pivot->value) {
      if (head_new == nullptr) head_new = current;

      previous = current;
      current = current->next;
    } else {
      if (previous != nullptr) previous->next = current->next;
      QElement<T> *temp = current->next;
      current->next = nullptr;
      tail->next = current;
      tail = current;
      current = temp;
    }
  }
  if (head_new == nullptr) head_new = pivot;

  tail_new = tail;

  return pivot;
}

template <typename T>
QElement<T> *Queue<T>::GetTail_(QElement<T> *current) {
  while (current != nullptr && current->next != nullptr)
    current = current->next;
  return current;
}

#endif /* <queue.h> included.  */