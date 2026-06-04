#include <stdio.h>
#include <string.h>

#define SIZE 5

typedef struct {
    char character;
    int frequency;
} HashEntry;

HashEntry hashTable[SIZE];

void insert(char c) {
    int index = c % SIZE;
    int start = index;

    while (1) {
        if (hashTable[index].character == '\0') {
            hashTable[index].character = c;
            hashTable[index].frequency = 1;
            break;
        }
        if (hashTable[index].character == c) {
            hashTable[index].frequency++;
            break;
        }
        index = (index + 1) % SIZE;
        if (index == start) {
            break;
        }
    }
}

int main() {
    char S[1005];
    if (scanf("%s", S) != 1) return 0;

    for (int i = 0; i < SIZE; i++) {
        hashTable[i].character = '\0';
        hashTable[i].frequency = 0;
    }

    for (int i = 0; S[i] != '\0'; i++) {
        insert(S[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i].character != '\0') {
            printf("%c %d\n", hashTable[i].character, hashTable[i].frequency);
        }
    }

    return 0;
}`