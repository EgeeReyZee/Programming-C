#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void main() {

    printf("Enter list1 data: \n");
    linkedList1* list1 = makeList();
    reverse(list1);
    printList(list1);

    printf("Enter list2 data: \n");
    linkedList1* list2 = makeList();
    printList(list2);

    nodeS *S = (nodeS *)malloc(sizeof(nodeS));
    linkedList3 *listMain = (linkedList3*)malloc(sizeof(linkedList3));
    listMain = linking(list2, list1);
    S->start = listMain->head;
    
    printf("Управление списком (A/4 - в начало, D/6 - вправо, W/8 - вверх, S/2 - вниз, Q - выход, E - на указатель):\n");
    char command;
    node3 *head = listMain->head;
    node3 *currentMian = head;
    node1 *currentOpt;
    char *curr = "S";
    printf("Вы сейчас на указателе S\n");
    while (1) {
        scanf("%c", &command);
        if ((command == 'D' || command == '6' || command == 'd') && curr == "S") {
            curr = "M";
            currentMian = head;
            printf("Main list\nUp data %d\nDown data %d\n", currentMian->toListUp->data, currentMian->toListDown->data);
        }
        else if ((command == 'D' || command == '6' || command == 'd') && curr == "M") {
            currentMian = currentMian->next;
            if (currentMian->toListDown != NULL && currentMian->toListUp != NULL)
                printf("Main list\nUp data %d\nDown data %d\n", currentMian->toListUp->data, currentMian->toListDown->data);
            else if (currentMian->toListDown == NULL && currentMian->toListUp != NULL)
                printf("Main list\nUp data %d\nDown data not found\n", currentMian->toListUp->data);
            else if (currentMian->toListDown != NULL && currentMian->toListUp == NULL)
                printf("Main list\nUp data not found\nDown data %d\n", currentMian->toListDown->data);
        }
        else if ((command == 'D' || command == '6' || command == 'd') && curr == "O") {
            if (currentOpt->next != NULL) {
                currentOpt = currentOpt->next;
                printf("Data: %d\n", currentOpt->data);
            }
            else printf("Правее элементов нет\n");
        }   
        else if ((command == 'W' || command == '8' || command == 'w') && curr == "M") {
            curr = "O";
            currentOpt = currentMian->toListUp;
            printf("Data: %d\n", currentOpt->data);
        }
        else if ((command == 'W' || command == '8' || command == 'w') && curr == "O") {
            printf("Выше элементов нет. Сейчас вы в верхнем списке на узле %d\n", currentOpt->data);
        }
        else if ((command == 'S' || command == '2' || command == 's') && curr == "M") {
            curr = "O";
            currentOpt = currentMian->toListDown;
            printf("Data: %d\n", currentOpt->data);
        }
        else if ((command == 'S' || command == '2' || command == 's') && curr == "O") {
            printf("Ниже элементов нет. Сейчас вы в нижнем списке на узле %d\n", currentOpt->data);
        }
        else if (command == 'A' || command == '4' || command == 'a') {
            curr = "M";
            currentMian = head;
            printf("Main list\nUp data %d\nDown data %d\n", currentMian->toListUp->data, currentMian->toListDown->data);
        }
        else if (command == 'Q' || command == 'q') {
            exit(1);
        }
        else if (command == 'E' || command == 'e') {
            curr = "S";
            printf("Вы на указателе\n");
        }
    }
    free(list1);
    free(list2);
    free(listMain);
    free(S);
}
