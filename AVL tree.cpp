#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    int height;
    struct node *left;
    struct node *right;
} node;

node *head = NULL;

// ── helpers ──────────────────────────────────────────────────────────────────

int find_height(node *n)
{
    if (n == NULL) return 0;
    return n->height;
}

int find_max(int x, int y)
{
    return (x > y) ? x : y;
}

void get_height(node *n)
{
    n->height = 1 + find_max(find_height(n->left), find_height(n->right));
}

int balance(node *n)
{
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
node *rotate_right(node *y)
{
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
node *rotate_left(node *x)
{
    node *y  = x->right;
    node *t2 = y->left;

    y->left  = x;
    x->right = t2;

    get_height(x);  // x is now lower, update first
    get_height(y);  // y is now higher, update second

    return y;       // y is the new head
}

// ── node creation ─────────────────────────────────────────────────────────────

node *createNew(int val)
{
    node *n  = (node *)malloc(sizeof(node));
    n->val    = val;
    n->height = 1;
    n->left   = NULL;
    n->right  = NULL;
    return n;
}

// ── insertion ─────────────────────────────────────────────────────────────────

void push(node **n, int val)
{
    // 1. normal BST insert
    if (*n == NULL)
    {
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

    // Left-Left: new node inserted in left subtree of left child
    //
    //     z  (bal=+2)
    //    /
    //   y
    //  /
    // x  <-- inserted here
    //
    // fix: single rotate_right(z)
    //
    //   y
    //  / \
    // x   z
    if (bal > 1 && val < (*n)->left->val)
    {
        *n = rotate_right(*n);
        return;
    }

    // Right-Right: new node inserted in right subtree of right child
    //
    // z  (bal=-2)
    //  \
    //   y
    //    \
    //     x  <-- inserted here
    //
    // fix: single rotate_left(z)
    //
    //   y
    //  / \
    // z   x
    if (bal < -1 && val > (*n)->right->val)
    {
        *n = rotate_left(*n);
        return;
    }

    // Left-Right: new node inserted in right subtree of left child
    //
    //   z  (bal=+2)
    //  /
    // y
    //  \
    //   x  <-- inserted here
    //
    // fix: rotate_left(y) first, then rotate_right(z)
    //
    // step 1: rotate_left(y)      step 2: rotate_right(z)
    //   z                           x
    //  /                           / \
    // x              →            y   z
    //  \
    //   (was y, now x's left)
    if (bal > 1 && val > (*n)->left->val)
    {
        (*n)->left = rotate_left((*n)->left);
        *n = rotate_right(*n);
        return;
    }

    // Right-Left: new node inserted in left subtree of right child
    //
    // z  (bal=-2)
    //  \
    //   y
    //  /
    // x  <-- inserted here
    //
    // fix: rotate_right(y) first, then rotate_left(z)
    //
    // step 1: rotate_right(y)     step 2: rotate_left(z)
    // z                               x
    //  \                             / \
    //   x              →            z   y
    //  \
    //   (was y, now x's right)
    if (bal < -1 && val < (*n)->right->val)
    {
        (*n)->right = rotate_right((*n)->right);
        *n = rotate_left(*n);
        return;
    }
}

// ── deletion ──────────────────────────────────────────────────────────────────

node *delete_node(node *n, int target)
{
    if (n == NULL) return NULL;

    if (target < n->val)
        n->left = delete_node(n->left, target);
    else if (target > n->val)
        n->right = delete_node(n->right, target);
    else
    {
        // node found — three cases:
        //
        // case 1: no left child      case 2: no right child
        //
        //   n                n
        //  / \              / \
        // NULL  R    →  R  NULL  L   →  L
        //
        // case 3: two children — replace n with in-order successor (S),
        //         the leftmost node in the right subtree
        //
        //      n                  S
        //     / \       →        / \
        //    L   R              L   R'
        //       /                  (S removed from here)
        //      S
        node *temp = n;
        if (n->left == NULL)
        {
            n = n->right;
            free(temp);
            return n;
        }
        else if (n->right == NULL)
        {
            n = n->left;
            free(temp);
            return n;
        }
        else
        {
            temp = n->right;
            while (temp->left != NULL)
                temp = temp->left;
            n->val   = temp->val;
            n->right = delete_node(n->right, temp->val);
        }
    }

    get_height(n);
    int bal = balance(n);

    // same four rotation cases as insert, but use child balance
    // to determine LL/LR or RR/RL instead of the inserted value
    //
    // left heavy (bal=+2):
    //   child bf >= 0  →  Left-Left   →  rotate_right(n)
    //   child bf <  0  →  Left-Right  →  rotate_left(left), rotate_right(n)
    //
    // right heavy (bal=-2):
    //   child bf <= 0  →  Right-Right →  rotate_left(n)
    //   child bf >  0  →  Right-Left  →  rotate_right(right), rotate_left(n)

    if (bal > 1  && balance(n->left)  >= 0)
    {
        n = rotate_right(n);
        return n;
    }
    if (bal > 1  && balance(n->left)  <  0)
    {
        n->left = rotate_left(n->left);
        n = rotate_right(n);
        return n;
    }
    if (bal < -1 && balance(n->right) <= 0)
    {
        n = rotate_left(n);
        return n;
    }
    if (bal < -1 && balance(n->right) >  0)
    {
        n->right = rotate_right(n->right);
        n = rotate_left(n);
        return n;
    }

    return n;
}

// ── print in-order (should print sorted) ─────────────────────────────────────

void print(node *n)
{
    if (n == NULL) return;
    print(n->left);
    printf("val: %d  height: %d  balance: %d\n", n->val, n->height, balance(n));
    print(n->right);
}

// ── main ──────────────────────────────────────────────────────────────────────

int main()
{
    int x;
    scanf("%d", &x);

    for (int i = 0; i < x; i++)
    {
        int target;
        scanf("%d", &target);
        push(&head, target);
    }

    print(head);
    return 0;
}