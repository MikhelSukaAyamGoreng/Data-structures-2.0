#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    int height;
    struct node *left;
    struct node *right;
} node;

node *head = NULL;

// ── helpers ──────────────────────────────────────────────────────────────────

int find_height(node *n) {
    if (n == NULL) return 0;
    return n->height;
}

int find_max(int x, int y) {
    return (x > y) ? x : y;
}

void get_height(node *n) {
    n->height = 1 + find_max(find_height(n->left), find_height(n->right));
}

int balance(node *n) {
    if (n == NULL) return 0;
    return find_height(n->left) - find_height(n->right);
}

// ── rotations ────────────────────────────────────────────────────────────────

/*
 *     y                x
 *    / \             /   \
 *   x   T3   →    T1     y
 *  / \                  / \
 * T1  T2              T2  T3
 */
node *rotate_right(node *y) {
    node *x  = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left  = t2;

    get_height(y);  // y is now lower, update first
    get_height(x);  // x is now higher, update second

    return x;       // x is the new root
}

/*
 * x                    y
 *  \                 /   \
 *   y       →       x    T3
 *  / \               \
 * T2  T3             T2
 */
node *rotate_left(node *x) {
    node *y  = x->right;
    node *t2 = y->left;

    y->left  = x;
    x->right = t2;

    get_height(x);  // x is now lower, update first
    get_height(y);  // y is now higher, update second

    return y;       // y is the new root
}

// ── node creation ─────────────────────────────────────────────────────────────

node *createNew(int val) {
    node *n  = (node *)malloc(sizeof(node));
    n->val    = val;
    n->height = 1;      // new node is always a leaf
    n->left   = NULL;
    n->right  = NULL;
    return n;
}

// ── insertion ─────────────────────────────────────────────────────────────────

void push(node **n, int val) {
    // 1. normal BST insert
    if (*n == NULL) {
        *n = createNew(val);
        return;
    }

    if (val < (*n)->val)
        push(&(*n)->left, val);
    else if (val > (*n)->val)
        push(&(*n)->right, val);
    else
        return;  // duplicate, ignore

    // 2. update height on the way back up
    get_height(*n);

    // 3. check balance
    int bal = balance(*n);

    // Left-Left
    //     z
    //    /
    //   y
    //  /
    // x
    if (bal > 1 && val < (*n)->left->val) {
        *n = rotate_right(*n);
        return;
    }

    // Right-Right
    // z
    //  \
    //   y
    //    \
    //     x
    if (bal < -1 && val > (*n)->right->val) {
        *n = rotate_left(*n);
        return;
    }

    // Left-Right
    //   z
    //  /
    // y
    //  \
    //   x
    if (bal > 1 && val > (*n)->left->val) {
        (*n)->left = rotate_left((*n)->left);
        *n = rotate_right(*n);
        return;
    }

    // Right-Left
    // z
    //  \
    //   y
    //  /
    // x
    if (bal < -1 && val < (*n)->right->val) {
        (*n)->right = rotate_right((*n)->right);
        *n = rotate_left(*n);
        return;
    }
}

// ── print in-order (should print sorted) ─────────────────────────────────────

void print(node *n) {
    if (n == NULL) return;
    print(n->left);
    printf("val: %d  height: %d  balance: %d\n", n->val, n->height, balance(n));
    print(n->right);
}

// ── main ──────────────────────────────────────────────────────────────────────

int main() {
    int x;
    scanf("%d", &x);

    for (int i = 0; i < x; i++) {
        int target;
        scanf("%d", &target);
        push(&head, target);
    }

    print(head);
    return 0;
}