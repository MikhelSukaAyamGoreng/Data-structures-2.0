#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100

typedef struct node {
    int val;
    int key[max - 1];
    struct node *children[max];
    bool is_leaf;
}node;
node *head = NULL;

node *create_node(node *head) {
    node *newNode = (node*)malloc(sizeof(node));
    
}

int main() {
    int x; scanf("%d", &x);
    for (int i = 0; i < x; i++) {
        int target; scanf("%d", &target);
        head = push(head, target);
    }
}