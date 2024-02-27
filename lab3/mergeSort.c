#include "metrics.h"

void mergeSort(int data[], int start, int mid, int end) {
    int i, j, k;

    // seperate the data into two temp arrays
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int L[n1], R[n2];

    // fill the temp arrays
    for (i = 0; i < n1; i++)
        myCopy(&data[start + i], &L[i]);
    for (j = 0; j < n2; j++)
        myCopy(&data[mid + 1 + j], &R[j]);

    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2) {
        // if item in array L is smaller put it in the data array
        if (myCompare(L[i], R[j]) <= 0) {
            myCopy(&L[i], &data[k]);
            i++;
        } else {
            // else put item in array R in the data array
            myCopy(&R[j], &data[k]);
            j++;
        }
        // next spot in data array
        k++;
    }
    // put the rest of the items in L in the data array
    while (i < n1) {
        myCopy(&L[i], &data[k]);
        i++;
        k++;
    }
    // put the rest of the items in R in the data array
    while (j < n2) {
        myCopy(&R[j], &data[k]);
        j++;
        k++;
    }
}

void mySort(int data[], unsigned int first, unsigned int last) {
    if (first < last) {
        int mid = (first + last) / 2;
        
        // sort first and second halves
        mySort(data, first, mid);
        mySort(data, mid + 1, last);

        // merge sorted halves
        mergeSort(data, first, mid, last);
    }
}