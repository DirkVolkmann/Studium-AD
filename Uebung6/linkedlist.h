#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H 1

#include <iostream>

template <typename T>
class LLElement {
 public:
  T value;
  LLElement<T> *next;
};

template <typename T>
class LinkedList {
 private:
  LLElement<T> *head_;
  LLElement<T> *tail_;
  LLElement<T> *QuickSortR_(LLElement<T> *, LLElement<T> *);
  LLElement<T> *GetTail_(LLElement<T> *);
  LLElement<T> *Partition_(LLElement<T> *, LLElement<T> *, LLElement<T> *&,
                           LLElement<T> *&);

 public:
  LinkedList();
  ~LinkedList();
  void Append(T);
  void DeleteList();
  void DeleteValue(T);
  void Print();
  void QuickSort();
};

template <typename T>
LinkedList<T>::LinkedList() {
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  this->DeleteList();
}

template <typename T>
void LinkedList<T>::Append(T value_to_append) {
  LLElement<T> *element = new LLElement<T>;
  element->value = value_to_append;
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
void LinkedList<T>::DeleteList() {
  LLElement<T> *current = head_;
  LLElement<T> *next = nullptr;
  while (current != nullptr) {
    next = current->next;
    delete current;
    current = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
void LinkedList<T>::DeleteValue(T value_to_delete) {
  LLElement<T> *current = head_, *previous = nullptr;

  while (current != nullptr) {
    if (current->value == value_to_delete) {
      if (previous == nullptr)
        head_ = current->next;
      else
        previous->next = current->next;

      if (current == tail_) tail_ = previous;

      LLElement<T> *delete_this = current;
      current = current->next;
      delete delete_this;
    } else {
      previous = current;
      current = current->next;
    }
  }
}

template <typename T>
void LinkedList<T>::Print() {
  LLElement<T> *current = head_;
  while (current != nullptr) {
    std::cout << current->value << " ";
    current = current->next;
  }
  std::cout << std::endl;
}

template <typename T>
void LinkedList<T>::QuickSort() {
  LLElement<T> *head_new = QuickSortR_(head_, tail_);
  head_ = head_new;
  tail_ = GetTail_(head_);
}

template <typename T>
LLElement<T> *LinkedList<T>::QuickSortR_(LLElement<T> *head,
                                         LLElement<T> *tail) {
  if (head == nullptr || head == tail) return head;

  LLElement<T> *head_new = nullptr, *tail_new = nullptr;

  LLElement<T> *pivot = Partition_(head, tail, head_new, tail_new);

  if (head_new != pivot) {
    LLElement<T> *temp = head_new;
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
LLElement<T> *LinkedList<T>::Partition_(LLElement<T> *head, LLElement<T> *tail,
                                        LLElement<T> *&head_new,
                                        LLElement<T> *&tail_new) {
  LLElement<T> *pivot = tail, *previous = nullptr, *current = head;
  tail = pivot;

  while (current != pivot) {
    if (current->value < pivot->value) {
      if (head_new == nullptr) head_new = current;

      previous = current;
      current = current->next;
    } else {
      if (previous != nullptr) previous->next = current->next;
      LLElement<T> *temp = current->next;
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
LLElement<T> *LinkedList<T>::GetTail_(LLElement<T> *current) {
  while (current != nullptr && current->next != nullptr) current = current->next;
  return current;
}

#endif /* <linkedlist.h> included.  */