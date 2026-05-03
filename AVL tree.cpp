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

    return x;       // x is the new head
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

    return y;       // y is the new head
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

// delete
node *delete(node *head, int target) {
    if (head == NULL) return 0;
    node *temp = head;
    if (head->val > target ) {
        head->left = delete(head->left, target);
    }
    else if (head->val < target) {
        head->right = delete(head->right, target);
    }
    else {
        if (head->left == NULL) {
            head = head->right;
            free(temp);
            return head;
        }
        else if (head->right == NULL) {
            head = head->left;
            free(temp);
            return head;
        }
        else {
            temp = head->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            head->val = temp->val;    
            head->right = delete(head->right, temp->val);
        }
    }

    int target_balance = balance(head);
    if (target_balance < -1 && head->val > target) {
        head = rotate_left(head);
        return head;
    }
    else if (target_balance > 1 && head->val < target) {
        head = rotate_right(head);
        return head;
    }
    else if (target_balance > 1 && head->val > target) {
        head->right = rotate_right(head);
        head = rotate_right(head);
        return head;
    }
    else if (target_balance < -1 && head->val < target) {
        head->left = rotate_left(head);
        head = rotate_left(head);
        return head;
    }
    
    return head;
}

// ── print in-order (should print sorted) ─────────────────────────────────────

void print(node *n) {
    if (n == NULL) return;
    print(n->left);
    printf("val: %d  height: %d  balance: %d\n", n->val, n->height, balance(n));
    print(n->right);
}

// Delete
struct node* deleteNode(struct node* head, int key) {
    // 1. Standard BST Deletion
    if (head == NULL) return head;
    if (key < head->key)
        head->left = deleteNode(head->left, key);
    else if (key > head->key)
        head->right = deleteNode(head->right, key);
    else {
        // Node found
        if ((head->left == NULL) || (head->right == NULL)) {
            struct Node *temp = head->left ? head->left : head->right;
            if (temp == NULL) { // No child case
                temp = head;
                head = NULL;
            } else *head = *temp; // One child case
            free(temp);
        } else {
            // Two children case: get inorder successor
            struct Node* temp = minValueNode(head->right);
            head->key = temp->key;
            head->right = deleteNode(head->right, temp->key);
        }
    }

    if (head == NULL) return head;

    // 2. Update height and check balance
    head->height = 1 + max(height(head->left), height(head->right));
    int balance = getBalance(head);

    // 3. Rebalance the node (LL, LR, RR, RL cases)
    // ... rotation logic here ...
    return head;
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