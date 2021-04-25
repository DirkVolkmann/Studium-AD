#ifndef _RINGLIST_H
#define _RINGLIST_H 1

#include <iostream>

template <typename T>
class RLElement {
 public:
  T value;
  RLElement<T> *next;
};

template <typename T>
class RingList {
 private:
  RLElement<T> *head_;
  RLElement<T> *tail_;

 public:
  RingList();
  ~RingList();
  void Append(T);
  void DeleteList();
  void DeleteElement(RLElement<T> *);
  void Print();
  RLElement<T> *GetFirst();
};

template <typename T>
RingList<T>::RingList() {
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
RingList<T>::~RingList() {
  this->DeleteList();
}

template <typename T>
void RingList<T>::Append(T value_to_append) {
  RLElement<T> *element = new RLElement<T>;
  element->value = value_to_append;
  element->next = head_;

  if (tail_ == nullptr) {
    head_ = element;
    tail_ = element;
  } else {
    tail_->next = element;
    tail_ = element;
  }
}

template <typename T>
void RingList<T>::DeleteList() {
  RLElement<T> *current = head_;
  RLElement<T> *next = nullptr;
  while (current != tail_) {
    next = current->next;
    delete current;
    current = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
void RingList<T>::DeleteElement(RLElement<T> *element_to_delete) {
  RLElement<T> *current = head_, *previous = nullptr;
  if (current == nullptr) return;

  do {
    if (current == element_to_delete) {
      if (previous == nullptr)
        head_ = current->next;
      else
        previous->next = current->next;

      if (current == tail_) tail_ = previous;

      RLElement<T> *delete_this = current;
      current = current->next;
      delete delete_this;
    } else {
      previous = current;
      current = current->next;
    }
  } while (current != head_);
}

template <typename T>
void RingList<T>::Print() {
  RLElement<T> *current = head_;
  if (current == nullptr) return;

  do {
    std::cout << current->value << " ";
    current = current->next;
  } while (current != head_);
  std::cout << std::endl;
}

template <typename T>
RLElement<T> *RingList<T>::GetFirst() {
  return head_;
}

#endif /* <ringlist.h> included.  */