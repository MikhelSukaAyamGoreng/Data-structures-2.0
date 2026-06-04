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
int findMax(node *head){
    if (head->right->height < head->left->height) {
        return head->left->height;
    }
    else {
        return head->right->height;
    }
}
void getHeight(node **head) {
    (*head)->height = 1 + findMax(*head);
}
int findHeight(node *head) {
    if (head == NULL) return 0;
    return head->height;
}
int findBalance (node *head) {
    return findHeight(head->left) - findHeight(head->right);
}
node *createNode(int target) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    newNode->val = target;
    return newNode;
}
node *rotateLeft(node *head) {
    node *x = head->right;
    node *t2 = x->left;

    x->left = head;
    head->right = t2;

    getHeight(&x);
    getHeight(&head);
    return x;
}
node *rotateRight(node *head) {
    node *x = head->left;
    node *t2 = x->right;

    x->right = head;
    head->left = t2;

    getHeight(&x);
    getHeight(&head);
    return x;
}

void insert (node **head, int targetVal) {
    node *newNode = createNode(targetVal);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    else if ((*head)->val < targetVal) {
        insert(&(*head)->right, targetVal);
    }
    else {
        insert(&(*head)->left, targetVal);
    }

    getHeight(&(*head));
    int balance = findBalance(*head);

    if (balance < -1 && (*head)->val < targetVal) {
        *head = rotateLeft(*head);
        return;
    }
    else if (balance > 1 && (*head)->val < targetVal) {
        *head = rotateRight(*head);
        return;
    }
    else if (balance > 1 && (*head)->val > targetVal) {
        (*head)->left = rotateLeft(*head);
        *head = rotateRight(*head);
        return;
    }
    else if (balance < -1 && (*head)->val < targetVal) {
        (*head)->right = rotateRight(*head);
        *head = rotateLeft(*head);
        return;
    }
    return;
}

void del(node **head, int targetVal) {
    if (targetVal > (*head)->val) {
        del(&(*head)->right, targetVal);
    }
    else if (targetVal < (*head)->val){
        del(&(*head)->left, targetVal);
    }
    else {
        node *temp = *head;
        if ((*head)->left == NULL) {
            (*head) = (*head)->right;
            free(temp);
        }
        else if ((*head)->right == NULL) {
            *head = (*head)->left;
            free(temp);
        }
        else {
            temp = (*head)->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            targetVal =  temp->val;
            del(&(*head)->right, targetVal);
        }
    }
    getHeight(&(*head));
    int balance = findBalance(*head);
    if (balance < -1 && (*head)->val < targetVal) {
        *head = rotateRight(*head);
        return;
    }
    else if (balance > 1 && (*head)->val < targetVal) {
        *head = rotateLeft(*head);
        return;
    }
    if (balance > 1 && (*head)->val > targetVal) {
        (*head)->left = rotateLeft(*head);
        *head = rotateRight(*head);
        return;
    }
    if (balance < -1 && (*head)->val < targetVal) {
        (*head)->right = rotateRight(*head);
        *head = rotateRight(*head);
        return;
    }

    return;
}

int main() {
    int x; scanf("%d", &x);
    for (int i = 0; i < x; i++) {
        int target; scanf("%d", &target);
    }
    return 0;
}