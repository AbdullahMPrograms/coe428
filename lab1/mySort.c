#include "mySort.h"

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void mySort(int array[], unsigned int num_elements) {
  int i, j;
  for (i = 0; i < num_elements - 1; i++) {
    for (j = 0; j < num_elements - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        swap(&array[j], &array[j + 1]);
      }
    }
  }
}
