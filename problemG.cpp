#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    int height;
    struct node *left;
    struct node *right;
}node;
node *root = NULL;

int findHeight(node *root) {
    if (root == NULL) return 0;
    return root->height;
}

int findMax(int a, int b) {
    if (a > b) return a;
    else return b;
}

void updateHeight(node **root) {
    (*root)->height = 1 + findMax(findHeight((*root)->left), findHeight((*root)->right));
}

int findBalance(node *root) {
    return findHeight(root->left) - findHeight(root->right);
}

node *createNode(int target, node *root) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->height = 1;
    newNode->val = target;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node *rotateLeft(node *x) {
    node *y = x->right;
    node *t2 = y->left;

    y->left = x;
    x->right = t2;
    
    updateHeight(&x);
    updateHeight(&y);
    return y;
}

node *rotateRight(node *x) {
    node *y = x->left;
    node *t2 = y->right;

    y->right = x;
    x->left = t2;
    
    updateHeight(&x);
    updateHeight(&y);
    return y;
}

void reBalance(node **root, int target) {
    if (*root == NULL) return;
    updateHeight(root);
    int balance = findBalance(*root);

    if (balance < -1) {
        if (findBalance((*root)->right) <= 0) *root = rotateLeft(*root);
        else {
            (*root)->right = rotateRight((*root)->right);
            *root = rotateLeft(*root);
            return;
        }
        
        if (balance > 1) {
            if (findBalance((*root)->left) >= 0) *root = rotateRight(*root);
            else {
                (*root)->left = rotateLeft((*root)->left);
                *root = rotateRight(*root);
                return;
            }
        } 
    }
    return;
}

void insert(node **root, int target) {
    if (*root == NULL) {
        node *newNode = createNode(target, *root);
        *root = newNode;
        return;
    }
    else if ((*root)->val > target) {
        insert(&(*root)->left, target);
    }
    else if ((*root)->val < target) {
        insert(&(*root)->right, target);
    }
    else return;

    reBalance(root, target);
    return;
} 

void deleteNode(node **root, int target) {
    if (*root == NULL) return;

    if ((*root)->val > target) {
        deleteNode(&(*root)->left, target);
    }
    else if ((*root)->val < target) {
        deleteNode(&(*root)->right, target);
    }
    else {
        if ((*root)->left == NULL) {
            node *temp = *root;
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL) {
            node *temp = *root;
            *root = (*root)->left;
            free(temp);
        }
        else {
            node *temp = (*root)->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            (*root)->val = temp->val;
            deleteNode(&(*root)->right, temp->val);
        }
    }

    reBalance(root, target);
    return;
}

int counter = 0;
int smallestK(node *root, int k) {
    if (root == NULL) return -1;
    int left = smallestK(root->left, k);
    if (left != -1) return left;
    if (++counter == k) return root->val;
    return smallestK(root->right, k);
}

int main() {
    int n, q, k; scanf("%d %d %d", &n, &q, &k);
    for (int i = 0; i < n; i++) {
        int target; scanf("%d", &target);
        insert(&root, target);
    }
    for (int i = 0; i < q; i++) {
        int target; scanf("%d", &target);
        deleteNode(&root, target);
        counter = 0;
        printf("%d\n", smallestK(root, k));
    }
    return 0;
}