#include "mySort.h"

void mySort(int data[], unsigned int first, unsigned int last) {
        int i, j, temp;

        for (i = first; i <= last; i++) {
            // set the first element as the temp variable (will be used to make comparisons with)
            temp = data[i];
            // number of elements in dataset - temp
            j = i - 1;

            // do while there are elements in the dataset and the compared element is greater then the selected "temp"
            while (j >= 0 && (myCompare(data[j], temp)) > 0) {
                mySwap(&data[j + 1], &data[j]);
                j--;
            }
            // place the temp element in the correct position
            myCopy(&temp, &data[j + 1]);
        }
}