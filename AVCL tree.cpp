#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    int height;
    struct node *left;
    struct node *right;
}node;
node *head = NULL;

node *createNew(int target, int target_height) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->val = target;
    
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node *right_rotation(node **head) {
    node *x = (*head)->left;
    node *y = x->right;

    x->right = *head;
    (*head)->right = y;

    (*head)->height = (*head)->height + 1;
    y->height = y->height + 1;
    return;
}

node *left_rotation(node **head) {
    node *x = (*head)->right;
    node *y = x->left;

    x->left = *head;
    (*head)->right = y;

    (*head)->height = (*head)->height + 1;
    y->height = y->height + 1;
    return;
}

int find_balance(node **head, int res) {
    if (*head == NULL) return res;
    else {
        find_balance(&(*head)->left, res - 1);
        find_balance(&(*head)->right, res + 1 );
    }
}

void push(node **head, int target, int target_height) {
    if (*head == NULL) {
        node *newNode = createNew(target, target_height);
        *head = newNode;
        return;
    }
    else if ((*head)->val > target) {
        push(&(*head)->left, target, target_height--);
    }
    else if ((*head)->val < target) {
        push(&(*head)->right, target, target_height++);
    }
    else {
        if ((*head)->height < 0 && (*head)->height < -1) {
            left_rotation(&(*head));
        }
        else if ((*head)->height > 0 && (*head)->height > 1) {
            right_rotation(&(*head));
        }
    }
}

int main() {
    int x;
    scanf("%d", &x);
    for (int i = 0; i < x; i++) {
        int target; scanf("%d", &target);
        push(&head, target);
    }
}