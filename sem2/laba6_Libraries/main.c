#include "functions.h"
// #include "functions.c"

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
