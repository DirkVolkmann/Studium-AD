#include <iostream>
#include "ringlist.h"

int main() {
  srand(time(NULL));

  unsigned int size = 49;
  RingList<unsigned int> values;
  for (int i = 1; i <= size; i++) {
    values.Append(i);
  }

  RLElement<unsigned int> *the_chosen_one = values.GetFirst();
  for (int i = 1; i <= 6; i++) {
    unsigned int skip = rand() % size;
    for (int j = 0; j <= skip; j++) {
      the_chosen_one = the_chosen_one->next;
    }
    std::cout << the_chosen_one->value << " ";
    RLElement<unsigned int> *temp = the_chosen_one->next;
    values.DeleteElement(the_chosen_one);
    the_chosen_one = temp;
    size--;
  }
  std::cout << std::endl;
}