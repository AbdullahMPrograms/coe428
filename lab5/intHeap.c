#include <stdlib.h>
#include <stdio.h>
/**
 *  The functions in this module implement a Heapdata structure
 *  of integers.
 */
static int heap[100];
static int size = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the heap property when a new element is added to the heap
// compare the added element with its parent and if the parent's value is less than the element's value, swap them
// this is required because the new element may be greater than its parent and we need to maintain the heap property
void heapifyUp(int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && heap[parent] < heap[index]) {
        swap(&heap[parent], &heap[index]);
        heapifyUp(parent);
    }
}

// Function to maintain the heap property when an element is removed from the heap
// compare the removed element with its children and if the element's value is less than either of its children's values, swap the element with its larger child
// this is required because the removed element may be less than its children and we need to maintain the heap property
void heapifyDown(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;

    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        heapifyDown(largest);
    }
}

/**
 * heapDelete() removes the biggest integer in the heap and returns it.
 *
 */

int heapDelete() {
    if (size == 0) {
        fprintf(stderr, "Error: Heap is empty.\n");
        return -1;
    }

    int max = heap[0];
    heap[0] = heap[--size];
    heapifyDown(0);

    return max;
}

/**
 *  addHeap(thing2add) adds the "thing2add" to the Heap.
 *
 */
void addHeap(int thing2add) {
    if (size >= 100) {
        fprintf(stderr, "Error: Heap is full.\n");
        return;
    }

    heap[size++] = thing2add;
    heapifyUp(size - 1);
}

int getHeapElement(int index) {
    if (index >= 0 && index < size)
        return heap[index];
    return -1;
}

/**
 * heapSize() returns the number of items in the Heap.
 *
 */
int heapSize()
{
    return size;
}
