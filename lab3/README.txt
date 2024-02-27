All requirements are working (mergeSort, insertionSort)

Q&A:
2) 
Insertion Sort:
Best Case (Array is already sorted):
Data: "1 2 3 4 5"
Comparisons: 4 (n-1)
Swaps: 0
Copy operations: 5 (n)
Time Complexity: O(n)

Average Case:
Data: "1 5 4 3 2"
Comparisons: 10 (n^2-n)/2
Swaps: 6 
Copy Operations: 5 (n)
Time Complexity: O(n^2)

Worst Case (Array is sorted in reverse order):
Data: "5 4 3 2 1"
Comparisons: 10 (n^2-n)/2 
Swaps: 10 
Copy Operations: 5 (n)
Time Complexity: O(n^2)

Merge Sort (same regardless of the input case):
Best Case: 
Data: "1 2 3 4 5" 
Comparisons: 7 
Swaps: 0
Copy Operations: 24
Time complexity is O(nlogn)

Worst Case: 
Data: "5 4 3 2 1" 
Comparisons: 5 
Swaps: 0
Copy Operations: 24
Time complexity is O(nlogn)

Average Case: 
Data: "1 5 4 3 2"
Comparisons: 7
Swaps: 0
Copy operations: 24
Time complexity is O(nlogn)