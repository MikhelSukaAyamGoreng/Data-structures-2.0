#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    int height;
    struct node *right;
    struct node *left;
}node;
node *head = NULL;

int find_height(node *head) {
    if (head == NULL) return 0;
    else return head->height;
}

int find_max(int x, int y) {
    if (x > y) return x;
    else if (x < y) return y;
    else return x;
}

void get_height(node *head) {
    head->height = find_max(find_height(head->left), find_height(head->right));
}

int find_balance(node *head) {
    if (head == NULL) return 0;
    else {
        return find_height(head->left) - find_height(head->right);
    }
}

node *create(int target) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->val = target;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
}

node *rotate_right(node *head) {
    node *x = head->left;
    node *y = x->right;

    x->right = head;
    head->right = y;

    get_height(head);
    get_height(x);
    return x;
}

node *rotate_left(node *head) {
    node *x = head->right;
    node *y = x->left;

    x->left = head;
    head->right = y;

    get_height(head);
    get_height(x);
    return x;
}

node *push(node *head, int target){
    node *newNode = create(target);
    if (head == NULL) return newNode;
    else if (head->val < target) {
        push(head->right, target);
    }
    else if (head->val > target) {
        push(head->left, target);
    }

    int balance =find_balance(head);

    if (balance > 1) {

    }
}

int main() {
    int x; scanf("%d", &x);
    for (int i = 0; i < x; i++) {
        int target; scanf("%d", &target);
        head = push(head, target);
    }
}