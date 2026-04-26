#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int val;
    int height;
    struct node *left;
    struct node *right;
}node;
node *head = NULL;

node *createNew(int target_val) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->val = target_val;
    newNode->height = 1;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

int find_height(node *head) {
    if (head == NULL) return 0;
    return head->height;
}

int find_max(int x, int y) {
    if (x > y) return x;
    else if (x < y) return y;
}

void get_height(node *head) {
    head->height =  1 + find_max(find_height(head->left), find_height(head->right)); 
}

int balance(node *head) {
    return find_height(head->left) - find_height(head->right);
}

node *right(node *head) {
    node *x = head->right;
    node *t2 = x->left;

    x->right = head;
    head->left = t2; 

    find_height(head);
    find_height(x);
    return head;
}

node *left(node *head) {
    node *x = head->left;
    node *t2 = x->right;

    x->left = head;
    head->right = t2;

    find_height(head);
    find_height(x);
    return head;
}

void push(node **head, int target_val) {
    node *newNode = createNew(target_val);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    else if ((*head)->val > target_val) {
        push(&(*head)->left, target_val);
    }
    else if ((*head)->val < target_val) {
        push(&(*head)->right, target_val);
    }
    else {
        if ((*head)->height > 1 && target_val < (*head)->left->val) {
            *head = right(*head);
        }
        else if ((*head)->height < -1 && target_val < (*head)->left->val) {
            *head = left(*head);
        }
        else if ((*head)->height > 1 && target_val > (*head)->right->val) {
            (*head)->left = left((*head)->left);
            *head = right(*head);
        }
        else if ((*head)->height < -1 && target_val < (*head)->right->val) {
            (*head)->right = right((*head)->right);
            *head = left(*head);
            return;
        }        
    }
}

void print(node *head) {
    if (head == NULL) return;
    else {
        print(head->left);
        printf("%d", head->val);
        print(head->right);
    }
}

int main() {
    int x; scanf("%d", &x);
    for (int i = 0; i < x; i++) {
        int target; scanf("%d", &target);
        push(&head, target);
    }

    print(head);
    return 0;
}