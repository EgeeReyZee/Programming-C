#include "functions.h"

linkedList1 *append(linkedList1 *list, int newData) {
    node1 *newElement = (node1*)malloc(sizeof(node1));
    newElement->data = newData;
    newElement->next = NULL;

    if (list->head == NULL) {
        list->head = newElement;
        return list;
    }

    node1* cur = list->head;
    while (cur->next != NULL)
        cur = cur->next;
    
    cur->next = newElement;
    list->tail = newElement;
    return list;
}

linkedList1 *reverse(linkedList1 *list) {
    node1 *current = list->head;
    node1 *prev = NULL;
    node1 *next = NULL;
    list->tail = list->head;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;

    return list;
}

int listCount(linkedList1* list) {
    int count = 0;
    node1 *current = list->head;
    while (current->next != NULL) {
        count += 1;
        current = current->next;
    }
    count += 1;
    return count;
}

linkedList3 *linking(linkedList1 *list1, linkedList1 *list2) {
    linkedList3 *listMain = (linkedList3*)malloc(sizeof(linkedList3));
    listMain->head = NULL;
    listMain->tail = NULL;
    node1 *current1 = list1->head;
    node1 *current2 = list2->head;
    int count1 = listCount(list1);
    int count2 = listCount(list2);
    int maxCount = (count1 > count2) ? count1 : count2;

    node3 *currentMain = NULL;

    for (int i = 0; i < maxCount; i++) {
        node3 *newNode = (node3*)malloc(sizeof(node3));
        newNode->toListUp = NULL;
        newNode->toListDown = NULL;
        newNode->next = NULL;

        if (listMain->head == NULL) {
            listMain->head = newNode;
            currentMain = newNode;
        } else {
            currentMain->next = newNode;
            currentMain = newNode;
        }

        if(i == maxCount - 1){
            listMain->tail = newNode;
        }
    }

    currentMain = listMain->head;
    current1 = list1->head;
    current2 = list2->head;

    int i = 0;
    while (current1 != NULL && i < maxCount) {
        currentMain->toListUp = current1;
        current1 = current1->next;
        if (currentMain->next != NULL)
            currentMain = currentMain->next;
        i++;
    }

    i = 0;
    currentMain = listMain->head;
    while (current2 != NULL && i < maxCount) {
        currentMain->toListDown = current2;
        current2 = current2->next;
        if (currentMain->next != NULL)
            currentMain = currentMain->next;
        i++;
    }
    listMain->tail->next = listMain->head;

    return listMain;
}

void printList(linkedList1* list) {
    node1* cur = list->head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

linkedList1* makeList() {
    linkedList1* list = (linkedList1*)malloc(sizeof(linkedList1));
    list->head = NULL;
    list->tail = NULL;
    int data;
    while(1) {
        scanf("%d", &data);
        if (data == 0)
            break;
        else
            list = append(list, data);
    }
    return list;
}
