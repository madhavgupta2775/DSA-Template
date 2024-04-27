#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define MAX 100000

// ================== DEPENDENCY INJECTION ==================

struct meow {
    int data;
    char lamao[20];
};

int* getData(void *data, int idx) {
    return &((struct meow *)data)[idx].data;
}

void sortData(void *data, int n) {
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
    if (*((int *)getData(data, j)) > *((int *)getData(data, j + 1))) {
        int temp = *((int *)getData(data, j));
        *((int *)getData(data, j)) = *((int *)getData(data, j + 1));
        *((int *)getData(data, j + 1)) = temp;
    }
    }
    }
}

#define DATA_TYPE struct meow
#define GET_DATA(obj) obj.data
#define PRINT_DATA(obj) printf("%d\n", obj.data)
#define PRINT_MEOW(obj) printf("%d %s\n", obj.data, obj.lamao)
#define NULL_DATA {0, ""}

// ================== DEPENDENCY INJECTION END ==================


// ================== MULTI FILE PROGRAMMING ==================

// to use functions from other files, include the header file
// #ifndef MYHEADER_H
// #define MYHEADER_H
// #include "myheader.h"
// #endif

// ================ MULTI FILE PROGRAMMING END ================

// ================== DYANMIC ARRAY ==================


struct dynamic_array {
    DATA_TYPE *arr;
    int count;
    int capacity;
};

typedef struct dynamic_array dynamic_array;
typedef struct dynamic_array * DARRAY;

DARRAY create_darray() {
    DARRAY d = (DARRAY)malloc(sizeof(dynamic_array));
    d->arr = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * MAX);
    d->count = 0;
    d->capacity = MAX;
    return d;
}

void add_darray(DARRAY d, DATA_TYPE data) {
    if (d->count == d->capacity) {
        d->capacity *= 2;
        d->arr = (DATA_TYPE *)
        realloc(d->arr, sizeof(DATA_TYPE) * d->capacity);
    }
    d->arr[d->count++] = data;
}

void remove_darray(DARRAY d, int index) {
    if (index < 0 || index >= d->count) {
        return;
    }
    for (int i = index; i < d->count - 1; i++) {
        d->arr[i] = d->arr[i + 1];
    }
    d->count--;
}

void print_darray_data(DARRAY d) {
    for (int i = 0; i < d->count; i++) {
        PRINT_DATA(d->arr[i]);
    }
    printf("\n");
}

void print_darray_meow(DARRAY d) {
    for (int i = 0; i < d->count; i++) {
        PRINT_MEOW(d->arr[i]);
    }
    printf("\n");
}

// ================== DYANMIC ARRAY END ==================


// ================== SIMPLE LINKED LIST ==================

struct node {
    DATA_TYPE data;
    struct node *next;
};

struct linked_list {
    int count;
    struct node *head;
};

typedef struct node node;
typedef struct linked_list linked_list;
typedef struct linked_list * LIST;
typedef struct node * NODE;

LIST create_list() {
    LIST l = (LIST)malloc(sizeof(linked_list));
    l->count = 0;
    l->head = NULL;
    return l;
}

NODE create_node(DATA_TYPE data) {
    NODE n = (NODE)malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    return n;
}

void add_node_at_index(LIST l, DATA_TYPE data, int index) {
    if (index < 0 || index > l->count) {
        return;
    }
    NODE n = create_node(data);
    if (l->head == NULL) {
        l->head = n;
    } else if (index == 0) {
        n->next = l->head;
        l->head = n;
    } else {
        NODE temp = l->head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        n->next = temp->next;
        temp->next = n;
    }
    l->count++;
}

void add_start(LIST l, DATA_TYPE data) {
    add_node_at_index(l, data, 0);
}

void add_end(LIST l, DATA_TYPE data) {
    add_node_at_index(l, data, l->count);
}

NODE get_node(LIST l, int index) {
    if (index < 0 || index >= l->count) {
        return NULL;
    }
    NODE temp = l->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

void remove_node(LIST l, int index) {
    if (index < 0 || index >= l->count) {
        return;
    }
    if (index == 0) {
        NODE temp = l->head;
        l->head = l->head->next;
        free(temp);
    } else {
        NODE temp = get_node(l, index - 1);
        NODE temp2 = temp->next;
        temp->next = temp2->next;
        free(temp2);
    }
    l->count--;
}

void print_list(LIST l) {
    NODE temp = l->head;
    while (temp != NULL) {
        PRINT_DATA(temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void rotate_list_left(LIST l, int k) {
    if (k <= 0) {
        return;
    }
    k = k % l->count;
    if (k == 0) {
        return;
    }
    NODE temp = l->head;
    for (int i = 0; i < k - 1; i++) {
        temp = temp->next;
    }
    NODE temp2 = temp->next;
    temp->next = NULL;
    l->head = temp2;
    while (temp2->next != NULL) {
        temp2 = temp2->next;
    }
    temp2->next = l->head;
}

void rotate_list_right(LIST l, int k) {
    if (k <= 0) {
        return;
    }
    k = k % l->count;
    if (k == 0) {
        return;
    }
    NODE temp = l->head;
    for (int i = 0; i < l->count - k - 1; i++) {
        temp = temp->next;
    }
    NODE temp2 = temp->next;
    temp->next = NULL;
    l->head = temp2;
    while (temp2->next != NULL) {
        temp2 = temp2->next;
    }
    temp2->next = l->head;
}

int detect_loop(LIST l) {
    NODE slow = l->head;
    NODE fast = l->head;
    while (slow != NULL && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

// ================== SIMPLE LINKED LIST END ==================

// =============== DOUBLY LINKED LIST WITHOUT TAIL ===============

struct dnode {
    DATA_TYPE data;
    struct dnode *next;
    struct dnode *prev;
};

struct doubly_linked_list {
    int count;
    struct dnode *head;
};

typedef struct dnode dnode;
typedef struct doubly_linked_list doubly_linked_list;
typedef struct doubly_linked_list * DLIST;
typedef struct dnode * DNODE;

DLIST create_dlist() {
    DLIST l = (DLIST)malloc(sizeof(doubly_linked_list));
    l->count = 0;
    l->head = NULL;
    return l;
}

DNODE create_dnode(DATA_TYPE data) {
    DNODE n = (DNODE)malloc(sizeof(dnode));
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void add_at_index_dnode(DLIST l, DATA_TYPE data, int index) {
    if (index < 0 || index > l->count) {
        return;
    }
    DNODE n = create_dnode(data);
    if (l->head == NULL) {
        l->head = n;
    } else if (index == 0) {
        n->next = l->head;
        l->head->prev = n;
        l->head = n;
    } else {
        DNODE temp = l->head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        n->next = temp->next;
        n->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = n;
        }
        temp->next = n;
    }
    l->count++;
}

DNODE get_dnode_at_index(DLIST l, int index) {
    if (index < 0 || index >= l->count) {
        return NULL;
    }
    DNODE temp = l->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

void add_start_dnode(DLIST l, DATA_TYPE data) {
    add_at_index_dnode(l, data, 0);
}

void add_end_dnode(DLIST l, DATA_TYPE data) {
    add_at_index_dnode(l, data, l->count);
}

void remove_at_index_dnode(DLIST l, int index) {
    if (index < 0 || index >= l->count) {
        return;
    }
    if (index == 0) {
        DNODE temp = l->head;
        l->head = l->head->next;
        if (l->head != NULL) {
            l->head->prev = NULL;
        }
        free(temp);
    } else {
        DNODE temp = l->head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        free(temp);
    }
    l->count--;
}

void remove_start_dnode(DLIST l) {
    remove_at_index_dnode(l, 0);
}

void remove_end_dnode(DLIST l) {
    remove_at_index_dnode(l, l->count - 1);
}

void print_dlist(DLIST l) {
    DNODE temp = l->head;
    while (temp != NULL) {
        PRINT_DATA(temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void print_dlist_reverse(DLIST l) {
    DNODE temp = l->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (temp != NULL) {
        PRINT_DATA(temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

void rotate_dlist_left(DLIST l, int k) {
    if (k <= 0) {
        return;
    }
    k = k % l->count;
    if (k == 0) {
        return;
    }
    DNODE temp = l->head;
    for (int i = 0; i < k - 1; i++) {
        temp = temp->next;
    }
    DNODE temp2 = temp->next;
    temp->next = NULL;
    temp2->prev = NULL;
    l->head = temp2;
    while (temp2->next != NULL) {
        temp2 = temp2->next;
    }
    temp2->next = l->head;
    l->head->prev = temp2;
}

void rotate_dlist_right(DLIST l, int k) {
    if (k <= 0) {
        return;
    }
    k = k % l->count;
    if (k == 0) {
        return;
    }
    DNODE temp = l->head;
    for (int i = 0; i < l->count - k - 1; i++) {
        temp = temp->next;
    }
    DNODE temp2 = temp->next;
    temp->next = NULL;
    temp2->prev = NULL;
    l->head = temp2;
    while (temp2->next != NULL) {
        temp2 = temp2->next;
    }
    temp2->next = l->head;
    l->head->prev = temp2;
}

void destroy_dlist(DLIST l) {
    DNODE temp = l->head;
    while (temp != NULL) {
        DNODE temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    free(l);
}

// =============== DOUBLY LINKED LIST WIHTOUT TAIL END ===============

// ================== DOUBLY LINKED LIST WITH TAIL ==================

struct dtail_node {
    DATA_TYPE data;
    struct dtail_node *next;
    struct dtail_node *prev;
};

struct doubly_linked_list_tail {
    int count;
    struct dtail_node *head;
    struct dtail_node *tail;
};

typedef struct dtail_node dtail_node;
typedef struct doubly_linked_list_tail doubly_linked_list_tail;
typedef struct doubly_linked_list_tail * DLIST_TAIL;
typedef struct dtail_node * DTAIL_NODE;

DLIST_TAIL create_dlist_tail() {
    DLIST_TAIL l = (DLIST_TAIL)malloc(sizeof(doubly_linked_list_tail));
    l->count = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

DTAIL_NODE create_dtail_node(DATA_TYPE data) {
    DTAIL_NODE n = (DTAIL_NODE)malloc(sizeof(dtail_node));
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void add_at_index_dtail_node(DLIST_TAIL l, DATA_TYPE data, int index) {
    if (index < 0 || index > l->count) {
        return;
    }
    DTAIL_NODE n = create_dtail_node(data);
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    } else if (index == 0) {
        n->next = l->head;
        l->head->prev = n;
        l->head = n;
    } else if (index == l->count) {
        n->prev = l->tail;
        l->tail->next = n;
        l->tail = n;
    } else {
        DTAIL_NODE temp = l->head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        n->next = temp->next;
        n->prev = temp;
        temp->next->prev = n;
        temp->next = n;
    }
    l->count++;
}

DTAIL_NODE get_dtail_node_at_index(DLIST_TAIL l, int index) {
    if (index < 0 || index >= l->count) {
        return NULL;
    }
    DTAIL_NODE temp = l->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

void add_start_dtail_node(DLIST_TAIL l, DATA_TYPE data) {
    add_at_index_dtail_node(l, data, 0);
}

void add_end_dtail_node(DLIST_TAIL l, DATA_TYPE data) {
    add_at_index_dtail_node(l, data, l->count);
}

void remove_at_index_dtail_node(DLIST_TAIL l, int index) {
    if (index < 0 || index >= l->count) {
        return;
    }
    if (index == 0) {
        DTAIL_NODE temp = l->head;
        l->head = l->head->next;
        if (l->head != NULL) {
            l->head->prev = NULL;
        }
        free(temp);
    } else if (index == l->count - 1) {
        DTAIL_NODE temp = l->tail;
        l->tail = l->tail->prev;
        l->tail->next = NULL;
        free(temp);
    } else {
        DTAIL_NODE temp = l->head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
    l->count--;
}

void remove_start_dtail_node(DLIST_TAIL l) {
    remove_at_index_dtail_node(l, 0);
}

void remove_end_dtail_node(DLIST_TAIL l) {
    remove_at_index_dtail_node(l, l->count - 1);
}

void print_dlist_tail(DLIST_TAIL l) {
    DTAIL_NODE temp = l->head;
    while (temp != NULL) {
        PRINT_DATA(temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void print_dlist_tail_reverse(DLIST_TAIL l) {
    DTAIL_NODE temp = l->tail;
    while (temp != NULL) {
        PRINT_DATA(temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

void destroy_dlist_tail(DLIST_TAIL l) {
    DTAIL_NODE temp = l->head;
    while (temp != NULL) {
        DTAIL_NODE temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    free(l);
}

// =============== DOUBLY LINKED LIST WITH TAIL END ===============

// ================== STACK USING DYNAMIC ARRAY ==================

struct stack {
    DATA_TYPE *arr;
    int count;
    int capacity;
};

typedef struct stack stack;
typedef struct stack * STACK;

STACK create_stack() {
    STACK s = (STACK)malloc(sizeof(stack));
    s->arr = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * MAX);
    s->count = 0;
    s->capacity = MAX;
    return s;
}

void push(STACK s, DATA_TYPE data) {
    if (s->count == s->capacity) {
        s->capacity *= 2;
        s->arr = (DATA_TYPE *)
        realloc(s->arr, sizeof(DATA_TYPE) * s->capacity);
    }
    s->arr[s->count++] = data;
}

DATA_TYPE pop(STACK s) {
    if (s->count == 0) {
        return;
    }
    return s->arr[--s->count];
}

DATA_TYPE top(STACK s) {
    if (s->count == 0) {
        return;
    }
    return s->arr[s->count - 1];
}

int is_empty(STACK s) {
    return s->count == 0;
}

int is_full(STACK s) {
    return s->count == s->capacity;
}

// ================ STACK USING DYNAMIC ARRAY END ================

// ================== STACK USING LINKED LIST ==================

struct LLstack {
    struct node *head;
    int count;
};

typedef struct LLstack LLstack;
typedef struct LLstack * LLSTACK;

LLSTACK create_LLstack() {
    LLSTACK s = (LLSTACK)malloc(sizeof(LLstack));
    s->head = NULL;
    s->count = 0;
    return s;
}

void push_LLstack(LLSTACK s, DATA_TYPE data) {
    NODE n = create_node(data);
    n->next = s->head;
    s->head = n;
    s->count++;
}

DATA_TYPE pop_LLstack(LLSTACK s) {
    if (s->count == 0) {
        return;
    }
    NODE temp = s->head;
    s->head = s->head->next;
    DATA_TYPE data = temp->data;
    free(temp);
    s->count--;
    return data;
}

DATA_TYPE top_LLstack(LLSTACK s) {
    if (s->count == 0) {
        return;
    }
    return s->head->data;
}

int is_empty_LLstack(LLSTACK s) {
    return s->count == 0;
}

// ================== STACK USING LINKED LIST END ==================

// ================== QUEUE USING DYNAMIC ARRAY ==================

struct queue {
    DATA_TYPE *arr;
    int front;
    int rear;
    int capacity;
};

typedef struct queue queue;
typedef struct queue * QUEUE;

QUEUE create_queue() {
    QUEUE q = (QUEUE)malloc(sizeof(queue));
    q->arr = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * MAX);
    q->front = 0;
    q->rear = 0;
    q->capacity = MAX;
    return q;
}

void enqueue(QUEUE q, DATA_TYPE data) {
    if ((q->rear + 1) % q->capacity == q->front) {
        return;
    }
    q->arr[q->rear] = data;
    q->rear = (q->rear + 1) % q->capacity;
}

DATA_TYPE dequeue(QUEUE q) {
    if (q->front == q->rear) {
        return;
    }
    DATA_TYPE data = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    return data;
}

DATA_TYPE front(QUEUE q) {
    if (q->front == q->rear) {
        return;
    }
    return q->arr[q->front];
}

DATA_TYPE rear(QUEUE q) {
    if (q->front == q->rear) {
        return;
    }
    return q->arr[q->rear - 1];
}

int is_empty_queue(QUEUE q) {
    return q->front == q->rear;
}

int is_full_queue(QUEUE q) {
    return (q->rear + 1) % q->capacity == q->front;
}

// ================ QUEUE USING DYNAMIC ARRAY END ================

// ================== QUEUE USING LINKED LIST ==================

struct LLqueue {
    struct node *front;
    struct node *rear;
    int count;
};

typedef struct LLqueue LLqueue;
typedef struct LLqueue * LLQUEUE;

LLQUEUE create_LLqueue() {
    LLQUEUE q = (LLQUEUE)malloc(sizeof(LLqueue));
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    return q;
}

void enqueue_LLqueue(LLQUEUE q, DATA_TYPE data) {
    NODE n = create_node(data);
    if (q->front == NULL) {
        q->front = n;
        q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
    q->count++;
}

DATA_TYPE dequeue_LLqueue(LLQUEUE q) {
    if (q->front == NULL) {
        return;
    }
    NODE temp = q->front;
    q->front = q->front->next;
    DATA_TYPE data = temp->data;
    free(temp);
    q->count--;
    return data;
}

DATA_TYPE front_LLqueue(LLQUEUE q) {
    if (q->front == NULL) {
        return;
    }
    return q->front->data;
}

DATA_TYPE rear_LLqueue(LLQUEUE q) {
    if (q->rear == NULL) {
        return;
    }
    return q->rear->data;
}

int is_empty_LLqueue(LLQUEUE q) {
    return q->front == NULL;
}

// ================== QUEUE USING LINKED LIST END ==================

// ================== DEQUE USING DYNAMIC ARRAY ==================

struct deque {
    DATA_TYPE *arr;
    int front;
    int rear;
    int capacity;
};

typedef struct deque deque;
typedef struct deque * DEQUE;

DEQUE create_deque() {
    DEQUE d = (DEQUE)malloc(sizeof(deque));
    d->arr = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * MAX);
    d->front = 0;
    d->rear = 0;
    d->capacity = MAX;
    return d;
}

void push_front(DEQUE d, DATA_TYPE data) {
    if ((d->rear + 1) % d->capacity == d->front) {
        return;
    }
    d->front = (d->front - 1 + d->capacity) % d->capacity;
    d->arr[d->front] = data;
}

void push_back(DEQUE d, DATA_TYPE data) {
    if ((d->rear + 1) % d->capacity == d->front) {
        return;
    }
    d->arr[d->rear] = data;
    d->rear = (d->rear + 1) % d->capacity;
}

DATA_TYPE pop_front(DEQUE d) {
    if (d->front == d->rear) {
        return;
    }
    DATA_TYPE data = d->arr[d->front];
    d->front = (d->front + 1) % d->capacity;
    return data;
}

DATA_TYPE pop_back(DEQUE d) {
    if (d->front == d->rear) {
        return;
    }
    d->rear = (d->rear - 1 + d->capacity) % d->capacity;
    return d->arr[d->rear];
}

DATA_TYPE front_deque(DEQUE d) {
    if (d->front == d->rear) {
        return;
    }
    return d->arr[d->front];
}

DATA_TYPE rear_deque(DEQUE d) {
    if (d->front == d->rear) {
        return;
    }
    return d->arr[(d->rear - 1 + d->capacity) % d->capacity];
}

int is_empty_deque(DEQUE d) {
    return d->front == d->rear;
}

int is_full_deque(DEQUE d) {
    return (d->rear + 1) % d->capacity == d->front;
}

// ================ DEQUE USING DYNAMIC ARRAY END ================

// ================== DEQUE USING LINKED LIST ==================

struct LLdeque {
    struct node *front;
    struct node *rear;
    int count;
};

typedef struct LLdeque LLdeque;
typedef struct LLdeque * LLDEQUE;

LLDEQUE create_LLdeque() {
    LLDEQUE d = (LLDEQUE)malloc(sizeof(LLdeque));
    d->front = NULL;
    d->rear = NULL;
    d->count = 0;
    return d;
}

void push_front_LLdeque(LLDEQUE d, DATA_TYPE data) {
    NODE n = create_node(data);
    if (d->front == NULL) {
        d->front = n;
        d->rear = n;
    } else {
        n->next = d->front;
        d->front = n;
    }
    d->count++;
}

void push_back_LLdeque(LLDEQUE d, DATA_TYPE data) {
    NODE n = create_node(data);
    if (d->front == NULL) {
        d->front = n;
        d->rear = n;
    } else {
        d->rear->next = n;
        d->rear = n;
    }
    d->count++;
}

DATA_TYPE pop_front_LLdeque(LLDEQUE d) {
    if (d->front == NULL) {
        return;
    }
    NODE temp = d->front;
    d->front = d->front->next;
    DATA_TYPE data = temp->data;
    free(temp);
    d->count--;
    return data;
}

DATA_TYPE pop_back_LLdeque(LLDEQUE d) {
    if (d->front == NULL) {
        return;
    }
    NODE temp = d->front;
    while (temp->next != d->rear) {
        temp = temp->next;
    }
    DATA_TYPE data = d->rear->data;
    free(d->rear);
    d->rear = temp;
    d->rear->next = NULL;
    d->count--;
    return data;
}

DATA_TYPE front_LLdeque(LLDEQUE d) {
    if (d->front == NULL) {
        return;
    }
    return d->front->data;
}

DATA_TYPE rear_LLdeque(LLDEQUE d) {
    if (d->rear == NULL) {
        return;
    }
    return d->rear->data;
}

int is_empty_LLdeque(LLDEQUE d) {
    return d->front == NULL;
}

// ================== DEQUE USING LINKED LIST END ==================

// ================== BINARY SEARCH TREE ==================

struct bst_node {
    DATA_TYPE data;
    struct bst_node *left;
    struct bst_node *right;
};

struct bst {
    struct bst_node *root;
};

typedef struct bst_node bst_node;
typedef struct bst bst;
typedef struct bst * BST;
typedef struct bst_node * BST_NODE;

BST create_bst() {
    BST b = (BST)malloc(sizeof(bst));
    b->root = NULL;
    return b;
}

BST_NODE create_bst_node(DATA_TYPE data) {
    BST_NODE n = (BST_NODE)malloc(sizeof(bst_node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void insert_bst(BST b, DATA_TYPE data) {
    BST_NODE n = create_bst_node(data);
    if (b->root == NULL) {
        b->root = n;
    } else {
        BST_NODE temp = b->root;
        while (1) {
            if (GET_DATA(data) < GET_DATA(temp->data)) {
                if (temp->left == NULL) {
                    temp->left = n;
                    break;
                }
                temp = temp->left;
            } else {
                if (temp->right == NULL) {
                    temp->right = n;
                    break;
                }
                temp = temp->right;
            }
        }
    }
}

void inorder_bst(BST_NODE n) {
    if (n == NULL) {
        return;
    }
    inorder_bst(n->left);
    PRINT_DATA(n->data);
    inorder_bst(n->right);
}

void inorder_bst_iterative(BST_NODE n) {
    if (n == NULL) {
        return;
    }
    BST_NODE current = n;
    BST_NODE pre;
    while (current != NULL) {
        if (current->left == NULL) {
            PRINT_DATA(current->data);
            current = current->right;
        } else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            } else {
                pre->right = NULL;
                PRINT_DATA(current->data);
                current = current->right;
            }
        }
    }
}

void preorder_bst(BST_NODE n) {
    if (n == NULL) {
        return;
    }
    PRINT_DATA(n->data);
    preorder_bst(n->left);
    preorder_bst(n->right);
}

void preorder_bst_iterative(BST_NODE n) {
    if (n == NULL) {
        return;
    }
    STACK s = create_stack();
    push(s, n);
    while (!is_empty(s)) {
        BST_NODE temp = pop(s);
        PRINT_DATA(temp->data);
        if (temp->right != NULL) {
            push(s, temp->right);
        }
        if (temp->left != NULL) {
            push(s, temp->left);
        }
    }
}

void postorder_bst(BST_NODE n) {
    if (n == NULL) {
        return;
    }
    postorder_bst(n->left);
    postorder_bst(n->right);
    PRINT_DATA(n->data);
}

void postorder_bst_iterative(BST_NODE n) {
    if (n == NULL) {
        return;
    }
    STACK s = create_stack();
    push(s, n);
    BST_NODE prev = NULL;
    while (!is_empty(s)) {
        BST_NODE current = top(s);
        if (prev == NULL || 
        prev->left == current || prev->right == current) {
            if (current->left != NULL) {
                push(s, current->left);
            } else if (current->right != NULL) {
                push(s, current->right);
            }
        } else if (current->left == prev) {
            if (current->right != NULL) {
                push(s, current->right);
            }
        } else {
            PRINT_DATA(current->data);
            pop(s);
        }
        prev = current;
    }
}

int search_bst(BST_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return 0;
    }
    if (GET_DATA(n->data) == GET_DATA(data)) {
        return 1;
    }
    if (GET_DATA(data) < GET_DATA(n->data)) {
        return search_bst(n->left, data);
    } else {
        return search_bst(n->right, data);
    }
}

DATA_TYPE min_bst(BST_NODE n) {
    if (n == NULL) {
        return;
    }
    while (n->left != NULL) {
        n = n->left;
    }
    return n->data;
}

DATA_TYPE max_bst(BST_NODE n) {
    if (n == NULL) {
        return;
    }
    while (n->right != NULL) {
        n = n->right;
    }
    return n->data;
}

int height_bst(BST_NODE n) {
    if (n == NULL) {
        return 0;
    }
    int left = height_bst(n->left);
    int right = height_bst(n->right);
    return 1 + (left > right ? left : right);
}

void delete_bst(BST_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return;
    }
    if (GET_DATA(data) == GET_DATA(n->data)) {
        if (n->left == NULL && n->right == NULL) {
            free(n);
            n = NULL;
        } else if (n->left == NULL) {
            BST_NODE temp = n;
            n = n->right;
            free(temp);
        } else if (n->right == NULL) {
            BST_NODE temp = n;
            n = n->left;
            free(temp);
        } else {
            BST_NODE temp = n->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            n->data = temp->data;
            delete_bst(n->right, temp->data);
        }
    } else if (GET_DATA(data) < GET_DATA(n->data)) {
        delete_bst(n->left, data);
    } else {
        delete_bst(n->right, data);
    }
}

DATA_TYPE kth_smallest(BST_NODE n, int k) {
    if (n == NULL) {
        return;
    }
    int left = height_bst(n->left);
    if (left == k - 1) {
        return n->data;
    } else if (left > k - 1) {
        return kth_smallest(n->left, k);
    } else {
        return kth_smallest(n->right, k - left - 1);
    }
}

int max_value_bst(BST_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return 0;
    }
    if (GET_DATA(data) < GET_DATA(n->data)) {
        return max_value_bst(n->left, data);
    } else if (GET_DATA(data) > GET_DATA(n->data)) {
        return max_value_bst(n->right, data);
    } else {
        if (n->right == NULL) {
            return 0;
        }
        BST_NODE temp = n->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return GET_DATA(temp->data);
    }
}

int min_value_bst(BST_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return 0;
    }
    if (GET_DATA(data) < GET_DATA(n->data)) {
        return min_value_bst(n->left, data);
    } else if (GET_DATA(data) > GET_DATA(n->data)) {
        return min_value_bst(n->right, data);
    } else {
        if (n->left == NULL) {
            return 0;
        }
        BST_NODE temp = n->left;
        while (temp->right != NULL) {
            temp = temp->right;
        }
        return GET_DATA(temp->data);
    }
}

int is_bst(BST_NODE n) {
    if (n == NULL) {
        return 1;
    }
    if (n->left != NULL && max_value_bst(n->left, n->data) > GET_DATA(n->data)) {
        return 0;
    }
    if (n->right != NULL && min_value_bst(n->right, n->data) < GET_DATA(n->data)) {
        return 0;
    }
    if (!is_bst(n->left) || !is_bst(n->right)) {
        return 0;
    }
    return 1;
}

// ================== BINARY SEARCH TREE END ==================

// =========== BINARY SEARCH TREE WITH PARENT POINTER ============

struct bst_parent_node {
    DATA_TYPE data;
    struct bst_parent_node *left;
    struct bst_parent_node *right;
    struct bst_parent_node *parent;
};

struct bst_parent {
    struct bst_parent_node *root;
};

typedef struct bst_parent_node bst_parent_node;
typedef struct bst_parent bst_parent;
typedef struct bst_parent * BST_PARENT;
typedef struct bst_parent_node * BST_PARENT_NODE;

BST_PARENT create_bst_parent() {
    BST_PARENT b = (BST_PARENT)malloc(sizeof(bst_parent));
    b->root = NULL;
    return b;
}

BST_PARENT_NODE create_bst_parent_node(DATA_TYPE data) {
    BST_PARENT_NODE n = 
    (BST_PARENT_NODE)malloc(sizeof(bst_parent_node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert_bst_parent(BST_PARENT b, DATA_TYPE data) {
    BST_PARENT_NODE n = create_bst_parent_node(data);
    if (b->root == NULL) {
        b->root = n;
    } else {
        BST_PARENT_NODE temp = b->root;
        while (1) {
            if (GET_DATA(data) < GET_DATA(temp->data)) {
                if (temp->left == NULL) {
                    temp->left = n;
                    n->parent = temp;
                    break;
                }
                temp = temp->left;
            } else {
                if (temp->right == NULL) {
                    temp->right = n;
                    n->parent = temp;
                    break;
                }
                temp = temp->right;
            }
        }
    }
}

void inorder_bst_parent(BST_PARENT_NODE n) {
    if (n == NULL) {
        return;
    }
    inorder_bst_parent(n->left);
    PRINT_DATA(n->data);
    inorder_bst_parent(n->right);
}

void inorder_bst_parent_iterative(BST_PARENT_NODE n) {
    if (n == NULL) {
        return;
    }
    BST_PARENT_NODE current = n;
    BST_PARENT_NODE pre;
    while (current != NULL) {
        if (current->left == NULL) {
            PRINT_DATA(current->data);
            current = current->right;
        } else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            } else {
                pre->right = NULL;
                PRINT_DATA(current->data);
                current = current->right;
            }
        }
    }
}

void preorder_bst_parent(BST_PARENT_NODE n) {
    if (n == NULL) {
        return;
    }
    PRINT_DATA(n->data);
    preorder_bst_parent(n->left);
    preorder_bst_parent(n->right);
}

void preorder_bst_parent_iterative(BST_PARENT_NODE n) {
    if (n == NULL) {
        return;
    }
    STACK s = create_stack();
    push(s, n);
    while (!is_empty(s)) {
        BST_PARENT_NODE temp = pop(s);
        PRINT_DATA(temp->data);
        if (temp->right != NULL) {
            push(s, temp->right);
        }
        if (temp->left != NULL) {
            push(s, temp->left);
        }
    }
}

void postorder_bst_parent(BST_PARENT_NODE n) {
    if (n == NULL) {
        return;
    }
    postorder_bst_parent(n->left);
    postorder_bst_parent(n->right);
    PRINT_DATA(n->data);
}

void postorder_bst_parent_iterative(BST_PARENT_NODE n) {
    if (n == NULL) {
        return;
    }
    STACK s = create_stack();
    push(s, n);
    BST_PARENT_NODE prev = NULL;
    while (!is_empty(s)) {
        BST_PARENT_NODE current = top(s);
        if (prev == NULL || 
        prev->left == current || prev->right == current) {
            if (current->left != NULL) {
                push(s, current->left);
            } else if (current->right != NULL) {
                push(s, current->right);
            }
        } else if (current->left == prev) {
            if (current->right != NULL) {
                push(s, current->right);
            }
        } else {
            PRINT_DATA(current->data);
            pop(s);
        }
        prev = current;
    }
}

int search_bst_parent(BST_PARENT_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return 0;
    }
    if (GET_DATA(n->data) == GET_DATA(data)) {
        return 1;
    }
    if (GET_DATA(data) < GET_DATA(n->data)) {
        return search_bst_parent(n->left, data);
    } else {
        return search_bst_parent(n->right, data);
    }
}

DATA_TYPE min_bst_parent(BST_PARENT_NODE n) {
    if (n == NULL) {
        return;
    }
    while (n->left != NULL) {
        n = n->left;
    }
    return n->data;
}

DATA_TYPE max_bst_parent(BST_PARENT_NODE n) {
    if (n == NULL) {
        return;
    }
    while (n->right != NULL) {
        n = n->right;
    }
    return n->data;
}

int height_bst_parent(BST_PARENT_NODE n) {
    if (n == NULL) {
        return 0;
    }
    int left = height_bst_parent(n->left);
    int right = height_bst_parent(n->right);
    return 1 + (left > right ? left : right);
}

void delete_bst_parent(BST_PARENT_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return;
    }
    if (GET_DATA(data) == GET_DATA(n->data)) {
        if (n->left == NULL && n->right == NULL) {
            if (n->parent->left == n) {
                n->parent->left = NULL;
            } else {
                n->parent->right = NULL;
            }
            free(n);
            n = NULL;
        } else if (n->left == NULL) {
            BST_PARENT_NODE temp = n;
            n = n->right;
            n->parent = temp->parent;
            free(temp);
        } else if (n->right == NULL) {
            BST_PARENT_NODE temp = n;
            n = n->left;
            n->parent = temp->parent;
            free(temp);
        } else {
            BST_PARENT_NODE temp = n->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            n->data = temp->data;
            delete_bst_parent(n->right, temp->data);
        }
    } else if (GET_DATA(data) < GET_DATA(n->data)) {
        delete_bst_parent(n->left, data);
    } else {
        delete_bst_parent(n->right, data);
    }
}

DATA_TYPE kth_smallest_parent(BST_PARENT_NODE n, int k) {
    if (n == NULL) {
        return;
    }
    int left = height_bst_parent(n->left);
    if (left == k - 1) {
        return n->data;
    } else if (left > k - 1) {
        return kth_smallest_parent(n->left, k);
    } else {
        return kth_smallest_parent(n->right, k - left - 1);
    }
}

// ======== BINARY SEARCH TREE WITH PARENT POINTER END =========

// ================== SPACE AND TIME ANALYSIS ==================

// #ifndef TIME_ANALYSIS
// #define TIME_ANALYSIS
// void time_analysis() {
//     struct timeval start, end;
//     gettimeofday(&start, NULL);
//     // code to be analyzed
//     gettimeofday(&end, NULL);
//     printf("Time taken: %ld microseconds\n", 
//     ((end.tv_sec * 1000000 + end.tv_usec) - 
//     (start.tv_sec * 1000000 + start.tv_usec)));
// }
// #endif

void time_analysis(void (*func)()) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    func();
    gettimeofday(&end, NULL);
    printf("Time taken: %ld microseconds\n", 
    ((end.tv_sec * 1000000 + end.tv_usec) - 
    (start.tv_sec * 1000000 + start.tv_usec)));
}

size_t heapMemoryAllocated = 0;
#define ADDITIONAL_MEMORY sizeof(int)

void *myMalloc(size_t size) {
    void *ptr = malloc(size + ADDITIONAL_MEMORY);
    if (ptr == NULL) {
        return NULL;
    }
    heapMemoryAllocated += size;
    *((int *)ptr) = size;
    return ptr + ADDITIONAL_MEMORY;
}

void myFree(void *ptr) {
    int size = *((int *)(ptr - ADDITIONAL_MEMORY));
    heapMemoryAllocated -= size;
    free(ptr - ADDITIONAL_MEMORY);
}

// #define malloc myMalloc
// #define free myFree

// ================== SPACE AND TIME ANALYSIS END ==================

// ================== INSERTION SORT ==================

void insert_in_order(DATA_TYPE *arr, int n, DATA_TYPE data) {
    int i = n - 1;
    while (i >= 0 && GET_DATA(arr[i]) > GET_DATA(data)) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = data;
}

void insertion_sort(DATA_TYPE *arr, int n) {
    for (int i = 1; i < n; i++) {
        insert_in_order(arr, i, arr[i]);
    }
}

// ================== INSERTION SORT END ==================

// ================== MERGE SORT ==================

void mergeAux(DATA_TYPE *l1, int s1, int e1, 
DATA_TYPE *l2, int s2, int e2, DATA_TYPE *arr, int s, int e) {
    int i = s1, j = s2, k = s;
    while (i <= e1 && j <= e2) {
        if (GET_DATA(l1[i]) < GET_DATA(l2[j])) {
            arr[k++] = l1[i++];
        } else {
            arr[k++] = l2[j++];
        }
    }
    while (i <= e1) {
        arr[k++] = l1[i++];
    }
    while (j <= e2) {
        arr[k++] = l2[j++];
    }
}

void merge(DATA_TYPE *arr, int s, int mid, int e) {
    DATA_TYPE *C = (DATA_TYPE *)
    malloc(sizeof(DATA_TYPE) * (e - s + 1));
    mergeAux(arr, s, mid, arr, mid + 1, e, C, 0, e - s);
    for (int i = s; i <= e; i++) {
        arr[i] = C[i - s];
    }
    free(C);
}

void merge_sort(DATA_TYPE *arr, int s, int e) {
    if (s < e) {
        int mid = (s + e) / 2;
        merge_sort(arr, s, mid);
        merge_sort(arr, mid + 1, e);
        merge(arr, s, mid, e);
    }
}

void mergeAux_recursive(DATA_TYPE *l1, int s1, int e1, 
DATA_TYPE *l2, int s2, int e2, DATA_TYPE *arr, int s, int e) {
    if (s1 > e1) {
        for (int i = s2; i <= e2; i++) {
            arr[s++] = l2[i];
        }
        return;
    }
    if (s2 > e2) {
        for (int i = s1; i <= e1; i++) {
            arr[s++] = l1[i];
        }
        return;
    }
    if (GET_DATA(l1[s1]) < GET_DATA(l2[s2])) {
        arr[s++] = l1[s1];
        mergeAux_recursive(l1, s1 + 1, e1, l2, s2, e2, arr, s + 1, e);
    } else {
        arr[s++] = l2[s2];
        mergeAux_recursive(l1, s1, e1, l2, s2 + 1, e2, arr, s + 1, e);
    }
}

void merge_recursive(DATA_TYPE *arr, int s, int mid, int e) {
    DATA_TYPE *C = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * (e - s + 1));
    mergeAux_recursive(arr, s, mid, arr, mid + 1, e, C, 0, e - s);
    for (int i = s; i <= e; i++) {
        arr[i] = C[i - s];
    }
    free(C);
}

void merge_sort_iterative(DATA_TYPE *arr, int n) {
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n - 1; j += 2 * i) {
            int mid = j + i - 1;
            int end = j + 2 * i - 1;
            if (end >= n) {
                end = n - 1;
            }
            merge(arr, j, mid, end);
        }
    }
}


// ================== MERGE SORT END ==================

// ================== FILE HANDLING ==================

// these functions will not be called, they are just for reference

// read csv file
void read_csv() {
    FILE *file = fopen("file.csv", "r");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }
    char line[1024];
    while (fgets(line, 1024, file)) {
        char *token = strtok(line, ",");
        while (token) {
            printf("%s ", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }
    fclose(file);
}

// read csv file containing array in the format size, [dat1, 
// dat2, dat3, ... , datn] there may be multiple lines
void read_csv_array() {
    FILE *file = fopen("file.csv", "r");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }
    char line[1024];
    while (fgets(line, 1024, file)) {
        char *token = strtok(line, ",");
        int size = atoi(token);
        int *arr = (int *)malloc(sizeof(int) * size);
        token = strtok(NULL, "[");
        token = strtok(NULL, ",");
        for (int i = 0; i < size; i++) {
            arr[i] = atoi(token);
            token = strtok(NULL, ",");
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
    }
    fclose(file);
}

// write array to csv file
void write_csv_array(int *arr, int size) {
    FILE *file = fopen("file.csv", "w");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }
    fprintf(file, "%d, [", size);
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d", arr[i]);
        if (i != size - 1) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
    fclose(file);
}

// ================== FILE HANDLING END ==================


// ================== STRING UTILS ==================

int lexico_compare(char *s1, char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) {
            return -1;
        } else if (s1[i] > s2[i]) {
            return 1;
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 0;
    } else if (s1[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

int lexico_compare_ignore_case(char *s1, char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] >= 'A' && s1[i] <= 'Z') {
            s1[i] += 32;
        }
        if (s2[i] >= 'A' && s2[i] <= 'Z') {
            s2[i] += 32;
        }
        if (s1[i] < s2[i]) {
            return -1;
        } else if (s1[i] > s2[i]) {
            return 1;
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 0;
    } else if (s1[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

int is_palindrome(char *s) {
    int n = strlen(s);
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int is_palindrome_ignore_case(char *s) {
    int n = strlen(s);
    for (int i = 0; i < n / 2; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
        if (s[n - i - 1] >= 'A' && s[n - i - 1] <= 'Z') {
            s[n - i - 1] += 32;
        }
        if (s[i] != s[n - i - 1]) {
            return 0;
        }
    }
    return 1;
}

// ================== STRING UTILS END ==================


// ============= LINKED LIST EXTRA UTILS =============

void reverse_linked_list(NODE *head) {
    NODE prev = NULL, current = *head, next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void reverse_linked_list_recursive(NODE *head) {
    if ((*head)->next == NULL) {
        return;
    }
    NODE first = (*head);
    NODE rest = first->next;
    reverse_linked_list_recursive(&rest);
    first->next->next = first;
    first->next = NULL;
    *head = rest;
}

// merge sort for linked list
void split_linked_list(NODE head, NODE *front, NODE *back) {
    NODE slow = head, fast = head->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = head;
    *back = slow->next;
    slow->next = NULL;
}

NODE merge_linked_list(NODE a, NODE b) {
    NODE result = NULL;
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }
    if (GET_DATA(a->data) <= GET_DATA(b->data)) {
        result = a;
        result->next = merge_linked_list(a->next, b);
    } else {
        result = b;
        result->next = merge_linked_list(a, b->next);
    }
    return result;
}

void merge_sort_linked_list(NODE *head) {
    NODE h = *head;
    NODE a, b;
    if (h == NULL || h->next == NULL) {
        return;
    }
    split_linked_list(h, &a, &b);
    merge_sort_linked_list(&a);
    merge_sort_linked_list(&b);
    *head = merge_linked_list(a, b);
}

void merge_sort_ll_iterative(NODE *head) {
    NODE start = *head;
    int len = 1;
    while (1) {
        NODE prev = NULL;
        NODE start1 = start;
        while (start1 != NULL) {
            NODE a = start1;
            int i = 0;
            for (i = 0; i < len && start1 != NULL; i++) {
                start1 = start1->next;
            }
            NODE b = start1;
            int j = 0;
            for (j = 0; j < len && start1 != NULL; j++) {
                start1 = start1->next;
            }
            while (i > 0 || j > 0) {
                if (i == 0) {
                    prev->next = b;
                    b = b->next;
                    j--;
                } else if (j == 0 || b == NULL) {
                    prev->next = a;
                    a = a->next;
                    i--;
                } else if (GET_DATA(a->data) < GET_DATA(b->data)) {
                    prev->next = a;
                    a = a->next;
                    i--;
                } else {
                    prev->next = b;
                    b = b->next;
                    j--;
                }
                prev = prev->next;
            }
            prev->next = start1;
        }
        if (start->next == NULL) {
            break;
        }
        len *= 2;
        start = *head;
    }
}

// insertions sort for linked list
void insert_in_order_ll(NODE *head, DATA_TYPE data) {
    NODE n = create_node(data);
    if (*head == NULL || GET_DATA(data) < GET_DATA((*head)->data)) {
        n->next = *head;
        *head = n;
    } else {
        NODE temp = *head;
        while (temp->next != NULL && 
        GET_DATA(temp->next->data) < GET_DATA(data)) {
            temp = temp->next;
        }
        n->next = temp->next;
        temp->next = n;
    }
}

void insertion_sort_ll(NODE *head) {
    NODE sorted = NULL;
    NODE current = *head;
    while (current != NULL) {
        NODE next = current->next;
        insert_in_order_ll(&sorted, current->data);
        current = next;
    }
    *head = sorted;
}

// ============= LINKED LIST EXTRA UTILS END =============

// ========== DOUBLY LINKED LIST EXTRA UTILS ===========

void reverse_doubly_linked_list(DNODE *head) {
    DNODE temp = NULL;
    DNODE current = *head;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        *head = temp->prev;
    }
}

void reverse_doubly_linked_list_recursive(DNODE *head) {
    DNODE temp = NULL;
    DNODE current = *head;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        *head = temp->prev;
    }
}

// merge sort for doubly linked list

void 
split_doubly_linked_list(DNODE head, DNODE *front, DNODE *back) {
    DNODE slow = head, fast = head->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = head;
    *back = slow->next;
    slow->next = NULL;
    (*back)->prev = NULL;
}

DNODE merge_doubly_linked_list(DNODE a, DNODE b) {
    DNODE result = NULL;
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }
    if (GET_DATA(a->data) <= GET_DATA(b->data)) {
        result = a;
        result->next = merge_doubly_linked_list(a->next, b);
        result->next->prev = result;
    } else {
        result = b;
        result->next = merge_doubly_linked_list(a, b->next);
        result->next->prev = result;
    }
    return result;
}

void merge_sort_doubly_linked_list(DNODE *head) {
    DNODE h = *head;
    DNODE a, b;
    if (h == NULL || h->next == NULL) {
        return;
    }
    split_doubly_linked_list(h, &a, &b);
    merge_sort_doubly_linked_list(&a);
    merge_sort_doubly_linked_list(&b);
    *head = merge_doubly_linked_list(a, b);
}

void merge_sort_dll_iterative(DNODE *head) {
    DNODE start = *head;
    int len = 1;
    while (1) {
        DNODE prev = NULL;
        DNODE start1 = start;
        while (start1 != NULL) {
            DNODE a = start1;
            int i = 0;
            for (i = 0; i < len && start1 != NULL; i++) {
                start1 = start1->next;
            }
            DNODE b = start1;
            int j = 0;
            for (j = 0; j < len && start1 != NULL; j++) {
                start1 = start1->next;
            }
            while (i > 0 || j > 0) {
                if (i == 0) {
                    prev->next = b;
                    b->prev = prev;
                    b = b->next;
                    j--;
                } else if (j == 0 || b == NULL) {
                    prev->next = a;
                    a->prev = prev;
                    a = a->next;
                    i--;
                } else if (GET_DATA(a->data) < GET_DATA(b->data)) {
                    prev->next = a;
                    a->prev = prev;
                    a = a->next;
                    i--;
                } else {
                    prev->next = b;
                    b->prev = prev;
                    b = b->next;
                    j--;
                }
                prev = prev->next;
            }
            prev->next = start1;
            if (start1 != NULL) {
                start1->prev = prev;
            }
        }
        if (start->next == NULL) {
            break;
        }
        len *= 2;
        start = *head;
    }
}

// insertions sort for doubly linked list

void insert_in_order_dll(DNODE *head, DATA_TYPE data) {
    DNODE n = create_dnode(data);
    if 
    (*head == NULL || GET_DATA(data) < GET_DATA((*head)->data)) {
        n->next = *head;
        if (*head != NULL) {
            (*head)->prev = n;
        }
        *head = n;
    } else {
        DNODE temp = *head;
        while (temp->next != NULL && 
        GET_DATA(temp->next->data) < GET_DATA(data)) {
            temp = temp->next;
        }
        n->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = n;
        }
        temp->next = n;
        n->prev = temp;
    }
}

void insertion_sort_dll(DNODE *head) {
    DNODE sorted = NULL;
    DNODE current = *head;
    while (current != NULL) {
        DNODE next = current->next;
        insert_in_order_dll(&sorted, current->data);
        current = next;
    }
    *head = sorted;
}

// ========== DOUBLY LINKED LIST EXTRA UTILS END ===========

// ============ AVL TREE USING BST ============

int is_height_balanced(bst_node *n) {
    if (n == NULL) {
        return 1;
    }
    int left = height_bst(n->left);
    int right = height_bst(n->right);
    if (abs(left - right) <= 1 && 
    is_height_balanced(n->left) && 
    is_height_balanced(n->right)) {
        return 1;
    }
    return 0;
}

BST_NODE left_rotate(BST_NODE x) {
    BST_NODE y = x->right;
    BST_NODE T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

BST_NODE right_rotate(BST_NODE y) {
    BST_NODE x = y->left;
    BST_NODE T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

BST_NODE insert_avl(BST_NODE root, DATA_TYPE data) {
    if (root == NULL) {
        return create_bst_node(data);
    }
    if (GET_DATA(data) < GET_DATA(root->data)) {
        root->left = insert_avl(root->left, data);
    } else if (GET_DATA(data) > GET_DATA(root->data)) {
        root->right = insert_avl(root->right, data);
    } else {
        return root;
    }
    int balance = is_height_balanced(root);
    if (!balance) {
        if (GET_DATA(data) < GET_DATA(root->data) && 
        GET_DATA(data) < GET_DATA(root->left->data)) {
            return right_rotate(root);
        }
        if (GET_DATA(data) > GET_DATA(root->data) && 
        GET_DATA(data) > GET_DATA(root->right->data)) {
            return left_rotate(root);
        }
        if (GET_DATA(data) < GET_DATA(root->data) && 
        GET_DATA(data) > GET_DATA(root->left->data)) {
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
        if (GET_DATA(data) > GET_DATA(root->data) && 
        GET_DATA(data) < GET_DATA(root->right->data)) {
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }
    }
    return root;
}

void delete_avl(BST_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return;
    }
    if (GET_DATA(data) == GET_DATA(n->data)) {
        if (n->left == NULL && n->right == NULL) {
            free(n);
            n = NULL;
        } else if (n->left == NULL) {
            BST_NODE temp = n;
            n = n->right;
            free(temp);
        } else if (n->right == NULL) {
            BST_NODE temp = n;
            n = n->left;
            free(temp);
        } else {
            BST_NODE temp = n->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            n->data = temp->data;
            delete_avl(n->right, temp->data);
        }
    } else if (GET_DATA(data) < GET_DATA(n->data)) {
        delete_avl(n->left, data);
    } else {
        delete_avl(n->right, data);
    }

    // rebalancing
    int balance = is_height_balanced(n);
    if (!balance) {
        if (GET_DATA(data) < GET_DATA(n->data) && 
        GET_DATA(data) < GET_DATA(n->left->data)) {
            n = right_rotate(n);
        }
        if (GET_DATA(data) > GET_DATA(n->data) && 
        GET_DATA(data) > GET_DATA(n->right->data)) {
            n = left_rotate(n);
        }
        if (GET_DATA(data) < GET_DATA(n->data) && 
        GET_DATA(data) > GET_DATA(n->left->data)) {
            n->left = left_rotate(n->left);
            n = right_rotate(n);
        }
        if (GET_DATA(data) > GET_DATA(n->data) && 
        GET_DATA(data) < GET_DATA(n->right->data)) {
            n->right = right_rotate(n->right);
            n = left_rotate(n);
        }
    }
}

int check_avl(BST bst) {
    return is_height_balanced(bst->root) && is_bst(bst->root);
}

// ============ AVL TREE USING BST END ============

// ============ AVL TREE ================

struct avl_node {
    DATA_TYPE data;
    struct avl_node *left;
    struct avl_node *right;
    int height;
};

typedef struct avl_node avl_node;
typedef struct avl_node * AVL_NODE;

struct avl_tree {
    AVL_NODE root;
};

typedef struct avl_tree avl_tree;
typedef struct avl_tree * AVL_TREE;

int height_avl(AVL_NODE n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

AVL_NODE create_avl_node(DATA_TYPE data) {
    AVL_NODE n = (AVL_NODE)malloc(sizeof(avl_node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

AVL_TREE create_avl_tree() {
    AVL_TREE t = (AVL_TREE)malloc(sizeof(avl_tree));
    t->root = NULL;
    return t;
}

AVL_NODE right_rotate_avl(AVL_NODE y) {
    AVL_NODE x = y->left;
    AVL_NODE T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height_avl(y->left), height_avl(y->right)) + 1;
    x->height = max(height_avl(x->left), height_avl(x->right)) + 1;
    return x;
}

AVL_NODE left_rotate_avl(AVL_NODE x) {
    AVL_NODE y = x->right;
    AVL_NODE T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height_avl(x->left), height_avl(x->right)) + 1;
    y->height = max(height_avl(y->left), height_avl(y->right)) + 1;
    return y;
}

int get_balance(AVL_NODE n) {
    if (n == NULL) {
        return 0;
    }
    return height_avl(n->left) - height_avl(n->right);
}

AVL_NODE insert_avl_node(AVL_NODE root, DATA_TYPE data) {
    if (root == NULL) {
        return create_avl_node(data);
    }
    if (GET_DATA(data) < GET_DATA(root->data)) {
        root->left = insert_avl_node(root->left, data);
    } else if (GET_DATA(data) > GET_DATA(root->data)) {
        root->right = insert_avl_node(root->right, data);
    } else {
        return root;
    }
    root->height = 1 + max(height_avl(root->left), height_avl(root->right));
    int balance = get_balance(root);
    if (balance > 1 && GET_DATA(data) < GET_DATA(root->left->data)) {
        return right_rotate_avl(root);
    }
    if (balance < -1 && GET_DATA(data) > GET_DATA(root->right->data)) {
        return left_rotate_avl(root);
    }
    if (balance > 1 && GET_DATA(data) > GET_DATA(root->left->data)) {
        root->left = left_rotate_avl(root->left);
        return right_rotate_avl(root);
    }
    if (balance < -1 && GET_DATA(data) < GET_DATA(root->right->data)) {
        root->right = right_rotate_avl(root->right);
        return left_rotate_avl(root);
    }
    return root;
}

void delete_avl_node(AVL_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return;
    }
    if (GET_DATA(data) == GET_DATA(n->data)) {
        if (n->left == NULL && n->right == NULL) {
            free(n);
            n = NULL;
        } else if (n->left == NULL) {
            AVL_NODE temp = n;
            n = n->right;
            free(temp);
        } else if (n->right == NULL) {
            AVL_NODE temp = n;
            n = n->left;
            free(temp);
        } else {
            AVL_NODE temp = n->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            n->data = temp->data;
            delete_avl_node(n->right, temp->data);
        }
    } else if (GET_DATA(data) < GET_DATA(n->data)) {
        delete_avl_node(n->left, data);
    } else {
        delete_avl_node(n->right, data);
    }

    // rebalancing
    n->height = 1 + max(height_avl(n->left), height_avl(n->right));
    int balance = get_balance(n);
    if (balance > 1 && GET_DATA(data) < GET_DATA(n->left->data)) {
        n = right_rotate_avl(n);
    }
    if (balance < -1 && GET_DATA(data) > GET_DATA(n->right->data)) {
        n = left_rotate_avl(n);
    }
    if (balance > 1 && GET_DATA(data) > GET_DATA(n->left->data)) {
        n->left = left_rotate_avl(n->left);
        n = right_rotate_avl(n);
    }
    if (balance < -1 && GET_DATA(data) < GET_DATA(n->right->data)) {
        n->right = right_rotate_avl(n->right);
        n = left_rotate_avl(n);
    }
}

AVL_NODE search_avl(AVL_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return NULL;
    }
    if (GET_DATA(data) == GET_DATA(n->data)) {
        return n;
    }
    if (GET_DATA(data) < GET_DATA(n->data)) {
        return search_avl(n->left, data);
    }
    return search_avl(n->right, data);
}

// ============ AVL TREE END ================

// ============ AVL TREE USING BST WITH PARENT POINTER ============

int height_bst_parent(BST_PARENT_NODE n) {
    if (n == NULL) {
        return 0;
    }
    int left = height_bst_parent(n->left);
    int right = height_bst_parent(n->right);
    return 1 + (left > right ? left : right);
}

int get_balance_bst_parent(BST_PARENT_NODE n) {
    if (n == NULL) {
        return 0;
    }
    return height_bst_parent(n->left) - height_bst_parent(n->right);
}

BST_PARENT_NODE right_rotate_bst_parent(BST_PARENT_NODE y) {
    BST_PARENT_NODE x = y->left;
    BST_PARENT_NODE T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

BST_PARENT_NODE left_rotate_bst_parent(BST_PARENT_NODE x) {
    BST_PARENT_NODE y = x->right;
    BST_PARENT_NODE T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

BST_PARENT_NODE insert_avl_bst_parent_iterative(BST_PARENT_NODE root, DATA_TYPE data) {
    BST_PARENT_NODE n = create_bst_parent_node(data);
    if (root == NULL) {
        return n;
    }
    BST_PARENT_NODE parent = NULL;
    BST_PARENT_NODE current = root;
    while (current != NULL) {
        parent = current;
        if (GET_DATA(data) < GET_DATA(current->data)) {
            current = current->left;
        } else if (GET_DATA(data) > GET_DATA(current->data)) {
            current = current->right;
        } else {
            return root;
        }
    }
    n->parent = parent;
    if (GET_DATA(data) < GET_DATA(parent->data)) {
        parent->left = n;
    } else {
        parent->right = n;
    }
    BST_PARENT_NODE temp = n;
    while (temp != NULL) {
        int balance = get_balance_bst_parent(temp);
        if (balance > 1 && GET_DATA(data) < GET_DATA(temp->left->data)) {
            return right_rotate_bst_parent(temp);
        }
        if (balance < -1 && GET_DATA(data) > GET_DATA(temp->right->data)) {
            return left_rotate_bst_parent(temp);
        }
        if (balance > 1 && GET_DATA(data) > GET_DATA(temp->left->data)) {
            temp->left = left_rotate_bst_parent(temp->left);
            return right_rotate_bst_parent(temp);
        }
        if (balance < -1 && GET_DATA(data) < GET_DATA(temp->right->data)) {
            temp->right = right_rotate_bst_parent(temp->right);
            return left_rotate_bst_parent(temp);
        }
        temp = temp->parent;
    }
    return root;
}

void delete_avl_bst_parent_iterative(BST_PARENT_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return;
    }
    BST_PARENT_NODE parent = NULL;
    BST_PARENT_NODE current = n;
    while (current != NULL) {
        if (GET_DATA(data) == GET_DATA(current->data)) {
            break;
        }
        parent = current;
        if (GET_DATA(data) < GET_DATA(current->data)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (current == NULL) {
        return;
    }
    if (current->left == NULL && current->right == NULL) {
        if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
        current = NULL;
    } else if (current->left == NULL) {
        if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        current->right->parent = parent;
        free(current);
    } else if (current->right == NULL) {
        if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        current->left->parent = parent;
        free(current);
    } else {
        BST_PARENT_NODE temp = current->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        current->data = temp->data;
        delete_avl_bst_parent_iterative(current->right, temp->data);
    }

    // rebalancing
    BST_PARENT_NODE temp = parent;
    while (temp != NULL) {
        int balance = get_balance_bst_parent(temp);
        if (balance > 1 && GET_DATA(data) < GET_DATA(temp->left->data)) {
            temp = right_rotate_bst_parent(temp);
        }
        if (balance < -1 && GET_DATA(data) > GET_DATA(temp->right->data)) {
            temp = left_rotate_bst_parent(temp);
        }
        if (balance > 1 && GET_DATA(data) > GET_DATA(temp->left->data)) {
            temp->left = left_rotate_bst_parent(temp->left);
            temp = right_rotate_bst_parent(temp);
        }
        if (balance < -1 && GET_DATA(data) < GET_DATA(temp->right->data)) {
            temp->right = right_rotate_bst_parent(temp->right);
            temp = left_rotate_bst_parent(temp);
        }
        temp = temp->parent;
    }
}

BST_PARENT_NODE search_avl_bst_parent(BST_PARENT_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return NULL;
    }
    if (GET_DATA(data) == GET_DATA(n->data)) {
        return n;
    }
    if (GET_DATA(data) < GET_DATA(n->data)) {
        return search_avl_bst_parent(n->left, data);
    }
    return search_avl_bst_parent(n->right, data);
}

// ============ AVL TREE USING BST WITH PARENT POINTER END ============

// ============ 2-4 TREE ============

struct two_four_node {
    DATA_TYPE data[3];
    struct two_four_node *child[4];
    int num_keys;
};

typedef struct two_four_node two_four_node;
typedef struct two_four_node * TWO_FOUR_NODE;

struct two_four_tree {
    TWO_FOUR_NODE root;
};

typedef struct two_four_tree two_four_tree;
typedef struct two_four_tree * TWO_FOUR_TREE;

TWO_FOUR_NODE create_two_four_node(DATA_TYPE data) {
    TWO_FOUR_NODE n = (TWO_FOUR_NODE)malloc(sizeof(two_four_node));
    n->data[0] = data;
    n->data[1] = n->data[2] = NULL_DATA;
    n->child[0] = n->child[1] = n->child[2] = n->child[3] = NULL;
    n->num_keys = 1;
    return n;
}

TWO_FOUR_TREE create_two_four_tree() {
    TWO_FOUR_TREE t = (TWO_FOUR_TREE)malloc(sizeof(two_four_tree));
    t->root = NULL;
    return t;
}

void split_child(TWO_FOUR_NODE x, int i) {
    TWO_FOUR_NODE z = create_two_four_node(x->child[i]->data[2]);
    TWO_FOUR_NODE y = x->child[i];
    x->child[3] = x->child[2];
    x->child[2] = x->child[1];
    x->child[1] = z;
    for (int j = x->num_keys; j > i; j--) {
        x->child[j] = x->child[j - 1];
    }
    x->child[i + 1] = z;
    for (int j = x->num_keys - 1; j >= i; j--) {
        x->data[j + 1] = x->data[j];
    }
    x->data[i] = y->data[1];
    x->num_keys++;
    y->num_keys = 1;
}

void insert_non_full(TWO_FOUR_NODE x, DATA_TYPE data) {
    int i = x->num_keys - 1;
    if (x->child[0] == NULL) {
        while (i >= 0 && GET_DATA(data) < GET_DATA(x->data[i])) {
            x->data[i + 1] = x->data[i];
            i--;
        }
        x->data[i + 1] = data;
        x->num_keys++;
    } else {
        while (i >= 0 && GET_DATA(data) < GET_DATA(x->data[i])) {
            i--;
        }
        i++;
        if (x->child[i]->num_keys == 3) {
            split_child(x, i);
            if (GET_DATA(data) > GET_DATA(x->data[i])) {
                i++;
            }
        }
        insert_non_full(x->child[i], data);
    }
}

void insert_two_four_tree(TWO_FOUR_TREE t, DATA_TYPE data) {
    if (t->root == NULL) {
        t->root = create_two_four_node(data);
    } else {
        TWO_FOUR_NODE r = t->root;
        if (r->num_keys == 3) {
            TWO_FOUR_NODE s = create_two_four_node(r->data[1]);
            s->child[0] = r;
            split_child(s, 0);
            t->root = s;
            insert_non_full(s, data);
        } else {
            insert_non_full(r, data);
        }
    }
}

TWO_FOUR_NODE merge_nodes(TWO_FOUR_NODE x, TWO_FOUR_NODE y) {
    TWO_FOUR_NODE z = create_two_four_node(x->data[1]);
    z->child[0] = x->child[0];
    z->child[1] = x->child[1];
    z->child[2] = y->child[0];
    z->child[3] = y->child[1];
    z->num_keys = 1;
    return z;
}

TWO_FOUR_NODE search_two_four_tree(TWO_FOUR_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return NULL;
    }
    if (GET_DATA(data) == GET_DATA(n->data[0])) {
        return n;
    } else if (GET_DATA(data) < GET_DATA(n->data[0])) {
        return search_two_four_tree(n->child[0], data);
    } else if (n->num_keys > 1 && GET_DATA(data) == GET_DATA(n->data[1])) {
        return n;
    } else if (n->num_keys > 1 && GET_DATA(data) < GET_DATA(n->data[1])) {
        return search_two_four_tree(n->child[1], data);
    } else if (n->num_keys > 2 && GET_DATA(data) == GET_DATA(n->data[2])) {
        return n;
    } else if (n->num_keys > 2 && GET_DATA(data) < GET_DATA(n->data[2])) {
        return search_two_four_tree(n->child[2], data);
    } else {
        return search_two_four_tree(n->child[3], data);
    }
}

void delete_two_four_tree(TWO_FOUR_NODE n, DATA_TYPE data) {
    if (n == NULL) {
        return;
    }
    if (GET_DATA(data) == GET_DATA(n->data[0])) {
        if (n->child[0] == NULL) {
            free(n);
            n = NULL;
        } else {
            TWO_FOUR_NODE temp = n->child[0];
            while (temp->child[0] != NULL) {
                temp = temp->child[0];
            }
            n->data[0] = temp->data[0];
            delete_two_four_tree(n->child[0], temp->data[0]);
        }
    } else if (GET_DATA(data) == GET_DATA(n->data[1])) {
        if (n->child[1] == NULL) {
            free(n);
            n = NULL;
        } else {
            TWO_FOUR_NODE temp = n->child[1];
            while (temp->child[0] != NULL) {
                temp = temp->child[0];
            }
            n->data[1] = temp->data[0];
            delete_two_four_tree(n->child[1], temp->data[0]);
        }
    } else if (GET_DATA(data) == GET_DATA(n->data[2])) {
        if (n->child[2] == NULL) {
            free(n);
            n = NULL;
        } else {
            TWO_FOUR_NODE temp = n->child[2];
            while (temp->child[0] != NULL) {
                temp = temp->child[0];
            }
            n->data[2] = temp->data[0];
            delete_two_four_tree(n->child[2], temp->data[0]);
        }
    } else {
        int i = 0;
        while (i < n->num_keys && GET_DATA(data) > GET_DATA(n->data[i])) {
            i++;
        }
        delete_two_four_tree(n->child[i], data);
    }
}

// ============ 2-4 TREE END ============

// ============ HEAP ============

struct heap {
    DATA_TYPE *arr;
    int capacity;
    int size;
    int depth;
};

typedef struct heap heap;
typedef struct heap * HEAP;

HEAP create_heap(int capacity) {
    HEAP h = (HEAP)malloc(sizeof(heap));
    h->arr = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * capacity);
    h->capacity = capacity;
    h->size = 0;
    h->depth = 0;
    return h;
}

int parent(HEAP h, int i) {
    return (i - 1) / 2;
}

int left_child(HEAP h, int i) {
    return 2 * i + 1;
}

int right_child(HEAP h, int i) {
    return 2 * i + 2;
}

void insert_max_heap(HEAP h, DATA_TYPE data) {
    if (h->size == h->capacity) {
        return;
    }
    h->size++;
    int i = h->size - 1;
    h->arr[i] = data;
    while (i != 0 && GET_DATA(h->arr[parent(h, i)]) < GET_DATA(h->arr[i])) {
        DATA_TYPE temp = h->arr[i];
        h->arr[i] = h->arr[parent(h, i)];
        h->arr[parent(h, i)] = temp;
        i = parent(h, i);
    }
}

void insert_min_heap(HEAP h, DATA_TYPE data) {
    if (h->size == h->capacity) {
        return;
    }
    h->size++;
    int i = h->size - 1;
    h->arr[i] = data;
    while (i != 0 && GET_DATA(h->arr[parent(h, i)]) > GET_DATA(h->arr[i])) {
        DATA_TYPE temp = h->arr[i];
        h->arr[i] = h->arr[parent(h, i)];
        h->arr[parent(h, i)] = temp;
        i = parent(h, i);
    }
}

void max_heapify(HEAP h, int i) {
    int l = left_child(h, i);
    int r = right_child(h, i);
    int largest = i;
    if (l < h->size && GET_DATA(h->arr[l]) > GET_DATA(h->arr[largest])) {
        largest = l;
    }
    if (r < h->size && GET_DATA(h->arr[r]) > GET_DATA(h->arr[largest])) {
        largest = r;
    }
    if (largest != i) {
        DATA_TYPE temp = h->arr[i];
        h->arr[i] = h->arr[largest];
        h->arr[largest] = temp;
        max_heapify(h, largest);
    }
}

void min_heapify(HEAP h, int i) {
    int l = left_child(h, i);
    int r = right_child(h, i);
    int smallest = i;
    if (l < h->size && GET_DATA(h->arr[l]) < GET_DATA(h->arr[smallest])) {
        smallest = l;
    }
    if (r < h->size && GET_DATA(h->arr[r]) < GET_DATA(h->arr[smallest])) {
        smallest = r;
    }
    if (smallest != i) {
        DATA_TYPE temp = h->arr[i];
        h->arr[i] = h->arr[smallest];
        h->arr[smallest] = temp;
        min_heapify(h, smallest);
    }
}

void delete_heap(HEAP h) {
    free(h->arr);
    free(h);
}

int nodes_at_depth(HEAP h, int depth) {
    // go to the first node at the depth
    int i = pow(2, depth) - 1;
    int count = 0;
    while (i < h->size && i < pow(2, depth + 1) - 1) {
        count++;
        i++;
    }
    return count;
}

DATA_TYPE extract_min(HEAP h) {
    if (h->size == 0) {
        return NULL;
    }
    if (h->size == 1) {
        h->size--;
        return h->arr[0];
    }
    DATA_TYPE root = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    min_heapify(h, 0);
    return root;
}

DATA_TYPE extract_max(HEAP h) {
    if (h->size == 0) {
        return NULL;
    }
    if (h->size == 1) {
        h->size--;
        return h->arr[0];
    }
    DATA_TYPE root = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    max_heapify(h, 0);
    return root;
}

void build_max_heap(HEAP h) {
    for (int i = h->size / 2 - 1; i >= 0; i--) {
        max_heapify(h, i);
    }
}

void build_min_heap(HEAP h) {
    for (int i = h->size / 2 - 1; i >= 0; i--) {
        min_heapify(h, i);
    }
}

void heap_sort(HEAP h) {
    build_max_heap(h);
    for (int i = h->size - 1; i > 0; i--) {
        DATA_TYPE temp = h->arr[0];
        h->arr[0] = h->arr[i];
        h->arr[i] = temp;
        h->size--;
        max_heapify(h, 0);
    }
}

// ============ HEAP END ============

// ============ PRIOIRTY QUEUE ============

struct priority_queue {
    HEAP h;
};

typedef struct priority_queue priority_queue;
typedef struct priority_queue * PRIORITY_QUEUE;

PRIORITY_QUEUE create_priority_queue(int capacity) {
    PRIORITY_QUEUE pq = (PRIORITY_QUEUE)malloc(sizeof(priority_queue));
    pq->h = create_heap(capacity);
    return pq;
}

void push_front(PRIORITY_QUEUE pq, DATA_TYPE data) {
    insert_max_heap(pq->h, data);
}

void push_back(PRIORITY_QUEUE pq, DATA_TYPE data) {
    insert_min_heap(pq->h, data);
}

DATA_TYPE front_priority_queue(PRIORITY_QUEUE pq) {
    return pq->h->arr[0];
}

DATA_TYPE pop_front(PRIORITY_QUEUE pq) {
    return extract_max(pq->h);
}

DATA_TYPE pop_back(PRIORITY_QUEUE pq) {
    return extract_min(pq->h);
}

void increase_key(PRIORITY_QUEUE pq, int i, DATA_TYPE data) {
    pq->h->arr[i] = data;
    while (i != 0 && GET_DATA(pq->h->arr[parent(pq->h, i)]) < GET_DATA(pq->h->arr[i])) {
        DATA_TYPE temp = pq->h->arr[i];
        pq->h->arr[i] = pq->h->arr[parent(pq->h, i)];
        pq->h->arr[parent(pq->h, i)] = temp;
        i = parent(pq->h, i);
    }
}

void delete_priority_queue(PRIORITY_QUEUE pq) {
    delete_heap(pq->h);
    free(pq);
}

LIST merge_k_ll(LIST *lists, int k) {
    PRIORITY_QUEUE pq = create_priority_queue(k);
    for (int i = 0; i < k; i++) {
        push_front(pq, lists[i]->head->data);
        lists[i]->head = lists[i]->head->next;
    }
    LIST merged = create_list();
    while (pq->h->size > 0) {
        DATA_TYPE max = pop_front(pq);
        insert_in_order_ll(&merged->head, max);
        for (int i = 0; i < k; i++) {
            if (lists[i]->head != NULL && GET_DATA(lists[i]->head->data) == GET_DATA(max)) {
                push_front(pq, lists[i]->head->data);
                lists[i]->head = lists[i]->head->next;
                break;
            }
        }
    }
    delete_priority_queue(pq);
    return merged;
}

// ============ PRIOIRTY QUEUE END ============


// ============ PIVOT UTILS ============

int random_pivot(int low, int high) {
    srand(time(0));
    return low + rand() % (high - low);
}

int median_of_three(DATA_TYPE *arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (GET_DATA(arr[low]) > GET_DATA(arr[mid])) {
        DATA_TYPE temp = arr[low];
        arr[low] = arr[mid];
        arr[mid] = temp;
    }
    if (GET_DATA(arr[low]) > GET_DATA(arr[high])) {
        DATA_TYPE temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
    if (GET_DATA(arr[mid]) > GET_DATA(arr[high])) {
        DATA_TYPE temp = arr[mid];
        arr[mid] = arr[high];
        arr[high] = temp;
    }
    DATA_TYPE temp = arr[mid];
    arr[mid] = arr[high - 1];
    arr[high - 1] = temp;
    return high - 1;
}

int partition(DATA_TYPE *arr, int low, int high, int pivot) {
    DATA_TYPE pivot_data = arr[pivot];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (GET_DATA(arr[j]) < GET_DATA(pivot_data)) {
            i++;
            DATA_TYPE temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    DATA_TYPE temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int median_of_medians(DATA_TYPE *arr, int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int n = high - low + 1;
        int i;
        DATA_TYPE median[(n + 4) / 5];
        for (i = 0; i < n / 5; i++) {
            median[i] = arr[low + i * 5 + 2];
        }
        if (i * 5 < n) {
            median[i] = arr[low + i * 5 + 2];
            i++;
        }
        int med_of_med = (i == 1) ? i - 1 : median_of_medians(median, 0, i - 1, i / 2);
        int pos = partition(arr, low, high, med_of_med);
        if (pos - low == k - 1) {
            return pos;
        }
        if (pos - low > k - 1) {
            return median_of_medians(arr, low, pos - 1, k);
        }
        return median_of_medians(arr, pos + 1, high, k - pos + low - 1);
    }
    return -1;
}

int qselect(DATA_TYPE *arr, int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int pos = median_of_medians(arr, low, high, k);
        if (pos - low == k - 1) {
            return pos;
        }
        if (pos - low > k - 1) {
            return qselect(arr, low, pos - 1, k);
        }
        return qselect(arr, pos + 1, high, k - pos + low - 1);
    }
    return -1;
}

// ============ PIVOT UTILS END ============

// ============ PARTITION UTILS ============

int hoare_partition(DATA_TYPE *arr, int low, int high, int pivot) {
    DATA_TYPE pivot_data = arr[pivot];
    int i = low - 1;
    int j = high + 1;
    while (1) {
        do {
            i++;
        } while (GET_DATA(arr[i]) < GET_DATA(pivot_data));
        do {
            j--;
        } while (GET_DATA(arr[j]) > GET_DATA(pivot_data));
        if (i >= j) {
            return j;
        }
        DATA_TYPE temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int lomuto_partition(DATA_TYPE *arr, int low, int high, int pivot) {
    DATA_TYPE pivot_data = arr[pivot];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (GET_DATA(arr[j]) < GET_DATA(pivot_data)) {
            i++;
            DATA_TYPE temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    DATA_TYPE temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int three_way_partition(DATA_TYPE *arr, int low, int high, int pivot, int *i, int *j) {
    DATA_TYPE pivot_data = arr[pivot];
    *i = low - 1;
    *j = high + 1;
    int mid = low;
    while (mid < *j) {
        if (GET_DATA(arr[mid]) < GET_DATA(pivot_data)) {
            (*i)++;
            DATA_TYPE temp = arr[*i];
            arr[*i] = arr[mid];
            arr[mid] = temp;
            mid++;
        } else if (GET_DATA(arr[mid]) > GET_DATA(pivot_data)) {
            (*j)--;
            DATA_TYPE temp = arr[*j];
            arr[*j] = arr[mid];
            arr[mid] = temp;
        } else {
            mid++;
        }
    }

    return mid;
}

// ============ PARTITION UTILS END ============

// ============ QUICK SORT ============

void quick_sort(DATA_TYPE *arr, int low, int high) {
    if (low < high) {
        int pivot = random_pivot(low, high);
        int pi = hoare_partition(arr, low, high, pivot);
        quick_sort(arr, low, pi);
        quick_sort(arr, pi + 1, high);
    }
}

void quick_sort_iterative(DATA_TYPE *arr, int low, int high) {
    int stack[high - low + 1];
    int top = -1;
    stack[++top] = low;
    stack[++top] = high;
    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];
        int pivot = random_pivot(low, high);
        int pi = hoare_partition(arr, low, high, pivot);
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

void quick_sort_hybrid(DATA_TYPE *arr, int low, int high) {
    if (low < high) {
        if (high - low + 1 < 10) {
            insertion_sort(arr, low, high);
        } else {
            int pivot = random_pivot(low, high);
            int pi = hoare_partition(arr, low, high, pivot);
            quick_sort(arr, low, pi);
            quick_sort(arr, pi + 1, high);
        }
    }
}

void quick_sort_hybrid_iterative(DATA_TYPE *arr, int low, int high) {
    int stack[high - low + 1];
    int top = -1;
    stack[++top] = low;
    stack[++top] = high;
    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];
        if (high - low + 1 < 10) {
            insertion_sort(arr, low, high);
        } else {
            int pivot = random_pivot(low, high);
            int pi = hoare_partition(arr, low, high, pivot);
            if (pi - 1 > low) {
                stack[++top] = low;
                stack[++top] = pi - 1;
            }
            if (pi + 1 < high) {
                stack[++top] = pi + 1;
                stack[++top] = high;
            }
        }
    }
}

// ============ QUICK SORT END ============

// ============ COUNTING SORT ============

void counting_sort(DATA_TYPE *arr, int n, int k) {
    DATA_TYPE output[n];
    int count[k + 1];
    for (int i = 0; i <= k; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[GET_DATA(arr[i])]++;
    }
    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[GET_DATA(arr[i])] - 1] = arr[i];
        count[GET_DATA(arr[i])]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// ============ COUNTING SORT END ============

// ============ RADIX SORT ============

void counting_sort_radix(DATA_TYPE *arr, int n, int exp) {
    DATA_TYPE output[n];
    int count[10];
    for (int i = 0; i < 10; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[(GET_DATA(arr[i]) / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[(GET_DATA(arr[i]) / exp) % 10] - 1] = arr[i];
        count[(GET_DATA(arr[i]) / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(DATA_TYPE *arr, int n) {
    int max = GET_DATA(arr[0]);
    for (int i = 1; i < n; i++) {
        if (GET_DATA(arr[i]) > max) {
            max = GET_DATA(arr[i]);
        }
    }
    for (int exp = 1; max / exp > 0; exp *= 10) {
        counting_sort_radix(arr, n, exp);
    }
}


// binary quick sort
void radix_exchange_sort(DATA_TYPE *arr, int n, int bit, int low, int high) {
    if (low >= high || bit < 0) {
        return;
    }
    int i = low;
    int j = high;
    while (i < j) {
        while (i < j && !(GET_DATA(arr[i]) & (1 << bit))) {
            i++;
        }
        while (i < j && (GET_DATA(arr[j]) & (1 << bit))) {
            j--;
        }
        DATA_TYPE temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    if (!(GET_DATA(arr[high]) & (1 << bit))) {
        j++;
    }
    radix_exchange_sort(arr, n, bit - 1, low, j - 1);
    radix_exchange_sort(arr, n, bit - 1, j, high);
}

void radix_exchange_sort_iterative(DATA_TYPE *arr, int n) {
    int low = 0;
    int high = n - 1;
    int bit = 31;
    while (low < high && bit >= 0) {
        int i = low;
        int j = high;
        while (i < j) {
            while (i < j && !(GET_DATA(arr[i]) & (1 << bit))) {
                i++;
            }
            while (i < j && (GET_DATA(arr[j]) & (1 << bit))) {
                j--;
            }
            DATA_TYPE temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        if (!(GET_DATA(arr[high]) & (1 << bit))) {
            j++;
        }
        high = j - 1;
        bit--;
    }
}

// ============ RADIX SORT END ============

// ============ BUCKET SORT ============

void bucket_sort(DATA_TYPE *arr, int n) {
    int max = GET_DATA(arr[0]);
    for (int i = 1; i < n; i++) {
        if (GET_DATA(arr[i]) > max) {
            max = GET_DATA(arr[i]);
        }
    }
    max++;
    LIST *buckets = (LIST *)malloc(sizeof(LIST) * max);
    for (int i = 0; i < max; i++) {
        buckets[i] = create_list();
    }
    for (int i = 0; i < n; i++) {
        insert_in_order_ll(&buckets[GET_DATA(arr[i])]->head, arr[i]);
    }
    for (int i = 0, j = 0; i < max; i++) {
        NODE temp = buckets[i]->head;
        while (temp != NULL) {
            arr[j++] = temp->data;
            temp = temp->next;
        }
    }
}

void interval_sort(DATA_TYPE *arr, int n) {
    LIST *buckets = (LIST *)malloc(sizeof(LIST) * n);
    for (int i = 0; i < n; i++) {
        buckets[i] = create_list();
    }
    for (int i = 0; i < n; i++) {
        int index = GET_DATA(arr[i]) * n;
        insert_in_order_ll(&buckets[index]->head, arr[i]);
    }
    for (int i = 0; i < n; i++) {
        merge_sort_linked_list(&buckets[i]->head);
    }
    for (int i = 0, j = 0; i < n; i++) {
        NODE temp = buckets[i]->head;
        while (temp != NULL) {
            arr[j++] = temp->data;
            temp = temp->next;
        }
    }
}

// ============ BUCKET SORT END ============




