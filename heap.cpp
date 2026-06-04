#include <stdio.h>
#define MAX 100

int heap[MAX];
int size = 0;

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ==================== MAX HEAP FUNCTIONS ====================

void insertMax(int target) {
    heap[size] = target;
    int curr = size;
    size++;
    while (curr > 0) {
        int parent = (curr - 1) / 2;
        if (heap[parent] < heap[curr]) {
            swap(&heap[curr], &heap[parent]);
            curr = parent;
        }
        else break;
    }
}

int delMax() {
    if (size <= 0) return -1; // Guard clause for empty heap

    int val = heap[0];
    heap[0] = heap[size - 1];
    size--;
    
    int curr = 0; // FIXED: Start at root index 0
    while (1) {
        int left = (curr * 2) + 1;
        int right = (curr * 2) + 2;
        int largest = curr; // FIXED: Reset to current node each iteration

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }
        
        if (largest == curr) break;

        swap(&heap[curr], &heap[largest]);
        curr = largest;
    }
    return val;
}

// ==================== MIN HEAP FUNCTIONS ====================

void insertMin(int targetVal) { // FIXED: Renamed function
    heap[size] = targetVal;
    int curr = size;
    size++;    
    while (curr > 0) {
        int parent = (curr - 1) / 2; // FIXED: Added parentheses for precedence
        if (heap[parent] > heap[curr]) {
            swap(&heap[parent], &heap[curr]);
            curr = parent;
        }
        else break;
    }
}

int delMin() {
    if (size <= 0) return -1;

    int targetVal = heap[0];
    heap[0] = heap[size - 1];
    size--;
    
    int curr = 0; // FIXED: Start at root index 0
    while (1) {
        int left = (curr * 2) + 1;
        int right = (curr * 2) + 2;
        int min = curr; // FIXED: Reset to current node each iteration

        if (left < size && heap[left] < heap[min]) {
            min = left;
        }
        // FIXED: Compare right child against current minimum selection
        if (right < size && heap[right] < heap[min]) {
            min = right;
        }
        
        if (min == curr) break;

        swap(&heap[curr], &heap[min]); // FIXED: Swapping curr instead of size
        curr = min;
    }
    return targetVal;
}

int main() {
    // Code can be tested here by choosing either Max or Min heap functions!
    return 0;
}