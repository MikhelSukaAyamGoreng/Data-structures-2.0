#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 105
typedef struct node {
    int freq;
    char target;
} node;
node heap[MAX_SIZE];
int size = 0;
void swap(int a, int b) {
    node temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
int hasHigherPriority(node a, node b) {
    if (a.freq != b.freq) {
        return a.freq > b.freq;
    }
    return a.target > b.target;
}
void insert(char targetChar, int targetFreq) {
    heap[size].freq = targetFreq;
    heap[size].target = targetChar;
    int curr = size;
    size++;
    while (curr > 0) {
        int parent = (curr - 1) / 2;
        if (hasHigherPriority(heap[curr], heap[parent])) {
            swap(curr, parent);
            curr = parent;
        } else {
            break;
        }
    }
}
node delMax() {
    node val = heap[0];
    heap[0] = heap[size - 1];
    size--;
    int curr = 0;
    while (1) {
        int left = (curr * 2) + 1;
        int right = (curr * 2) + 2;
        int largest = curr;
        if (left < size && hasHigherPriority(heap[left], heap[largest])) {
            largest = left;
        }
        if (right < size && hasHigherPriority(heap[right], heap[largest])) {
            largest = right;
        }
        if (largest == curr) break;
        swap(curr, largest);
        curr = largest;
    }
    return val;
}
int main() {
    int x; 
    if (scanf("%d", &x) != 1) return 0;
    int count[256] = {0};
    char target[105];
    scanf("%s", target);
    for (int i = 0; target[i] != '\0'; i++) {
        count[(unsigned char)target[i]]++;
    }
    for (int i = 'A'; i <= 'Z'; i++) {
        if (count[i] > 0) {
            insert((char)i, count[i]);
        }
    }   
    int limit = (size < x) ? size : x;
    for (int i = 0; i < limit; i++) {
        node temp = delMax();
        printf("%c  %d\n", temp.target, temp.freq);
    }
    return 0;
}