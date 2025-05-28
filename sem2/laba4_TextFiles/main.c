#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void main(int argc,char *argv[]) {

    if (argc < 2) {
        printf("Мало аргументов. Введите ./lab4.exe .lab4.txt");
        exit(1);
    }
    int numberCounter = 0;
    int digitCounter = 0;
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("In %s:%d Error opening file\n", __FILE__, __LINE__);
        exit(1);
    }

    rewind(file);

    int c;
    while ((c = fgetc(file)) != EOF){
        if (c > 47 && c < 58) {
            digitCounter++;
        }
        else if (digitCounter > 0) {
            numberCounter++;
            digitCounter = 0;
        }
    }
    if (digitCounter > 0)
        numberCounter++;
    fclose(file);
    char numcnt[11];
    sprintf(numcnt, "\n%d", numberCounter);
    FILE *file2 = fopen(argv[1], "a");
    fprintf(file2, numcnt);
    fclose(file2);
    printf("%d\n", numberCounter);
}
