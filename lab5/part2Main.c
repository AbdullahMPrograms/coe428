#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "intHeap.h"
#include "intStack.h"

void printHeapAsXML(int index) {
    // check if the index is within the heap
    if (index >= heapSize())
        return;

    // Calculate the indices of the left and right children
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Print the current node as an XML element
    printf("<node id=\"%d\">", getHeapElement(index));

    // If the left/right child exists, recursively print it
    if (left < heapSize())
        printHeapAsXML(left);

    if (right < heapSize())
        printHeapAsXML(right);

    printf("</node>");
}

int main(int argc, char * argv[]) {
    int value;
    while (scanf("%d\n", &value) != EOF) {
        fprintf(stderr, "READING INPUT: %d\n", value);
        addHeap(value);
    }

    // If the heap is not empty, print it as XML
    if (heapSize() > 0)
        printHeapAsXML(0);

    printf("\n");
    while (heapSize() > 0) {
        // Delete the top element from the heap
        int value = heapDelete();
        printf("%d\n", value);
        // Push the deleted value onto the stack
        push(value);
    }

    while (!isEmpty()) {
        // Pop the top element from the stack
        int value = pop();
        // Print the popped value
        printf("%d\n", value);
    }

    exit(0);
}