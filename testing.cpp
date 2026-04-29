#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
    struct node *prev;
}node;
node *head = NULL;
node *tail = NULL;

node *reverse(node *head) {
    node *prev = NULL;
    node *curr = head;
    while (curr != NULL) {
        node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return head;
}


void doubly_reverse(node **head, node **tail) {
    if (*head == NULL) return;
    node *curr = *head;
    node *prev = NULL;
    while (curr != NULL) {
        node *temp = curr->prev;

        curr->prev = prev;
        curr->next = temp;

        prev = curr;
        curr = temp;
    }
}

int main() {

}
