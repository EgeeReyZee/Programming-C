#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

EXPORT linkedList1* makeList();

typedef struct node3 {
    struct node3 *next;
    struct node1 *toListUp;
    struct node1 *toListDown;
}node3;

typedef struct nodeS {
    struct node3 *start;
}nodeS;

typedef struct node1 {
    int data;
    struct node1 *next;
}node1;

typedef struct linkedList3 {
    struct node3 *head;
    struct node3 *tail;
}linkedList3;

typedef struct linkedList1 {
    struct node1 *head;
    struct node1 *tail;
}linkedList1;

linkedList1 *append(linkedList1 *list, int newData);

linkedList1 *reverse(linkedList1 *list);

int listCount(linkedList1* list);

linkedList3 *linking(linkedList1 *list1, linkedList1 *list2);

void printList(linkedList1* list);

linkedList1* makeList();
