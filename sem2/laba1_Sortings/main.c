#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 1000000

struct Student {
    char name[64];
    int mathGrade;
    int physicsGrade;
    int informaticsGrade;
    int totalGrade;
};

void swap(struct Student *stud1, struct Student *stud2) {
    struct Student temp = *stud1;
    *stud1 = *stud2;
    *stud2 = temp;
}

struct Student addStudent(char *name, int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, sizeof(newStudent.name) - 1);
    newStudent.name[sizeof(newStudent.name) - 1] = '\0';
    newStudent.mathGrade = math;
    newStudent.physicsGrade = phy;
    newStudent.informaticsGrade = inf;
    newStudent.totalGrade = math + phy + inf;
    free(name);
    return newStudent;
}

void printStudentInfo(struct Student data) {
    printf("Name: %s ", data.name);
    for (int i = 0; i < 64 - strlen(data.name); i++)
        printf(" ");
    printf("Math grade: %d    ", data.mathGrade);
    if (data.mathGrade < 10) printf("  ");
    else if(data.mathGrade < 100) printf(" ");
    printf("Physics grade: %d    ", data.physicsGrade);
    if (data.physicsGrade < 10) printf("  ");
    else if(data.physicsGrade < 100) printf(" ");
    printf("Informatics grade: %d    ", data.informaticsGrade);
    if (data.informaticsGrade < 10) printf("  ");
    else if(data.informaticsGrade < 100) printf(" ");
    printf("Total grade: %d\n", data.totalGrade);
}

void selectSort(struct Student arr[], int n) {
    int i, j, min_idx;
        for (i = 0; i < n - 1; i++) {
            min_idx = i;
            for (j = i + 1; j < n; j++) {
                if (arr[j].totalGrade < arr[min_idx].totalGrade)
                    min_idx = j;
            }
            if (min_idx != i) {
                swap(&arr[min_idx], &arr[i]);
            }
        }
}

void insertSort(struct Student arr[], int n) {
    for (int j = 1; j < n; j++) {
        int key = arr[j].totalGrade;
        struct Student keystud = arr[j];
        int i = j - 1;
        while (i > -1 && arr[i].totalGrade > key) {
            arr[i + 1] = arr[i];
            i = i - 1;
        }
        arr[i+1] = keystud;
    }
}

void shellSort(struct Student arr[], int n) {
    for (int i = n / 2; i > 0; i /= 2) {
        for (int j = i; j < n; ++j) {
            for (int k = j - i; k >= 0 && arr[k].totalGrade > arr[k + i].totalGrade; k -= i) {
                swap(&arr[k], &arr[k + i]);
            }
        }
    }
}

void countingSort(struct Student arr[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].totalGrade > max) 
            max = arr[i].totalGrade;
    }

    int *count = (int *)calloc(max + 1, sizeof(int));
    struct Student *newArr = (struct Student*)malloc(n*sizeof(struct Student));
    for (int i = 0; i < n; i++) {
        count[arr[i].totalGrade]++;
    }
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    for (int i = 0; i < n; i++) {
        newArr[count[arr[i].totalGrade] - 1] = arr[i];
        count[arr[i].totalGrade]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = newArr[i];
    }
    free(count);
    free(newArr);
}

int partition(struct Student arr[], int low, int high) {
    int pivot = arr[high].totalGrade;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].totalGrade > pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(struct Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// const char* consonants[] = {"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "y", "z"};
// const char* vowels[] = {"a", "e", "i", "o", "u"};
// const int num_consonants = sizeof(consonants) / sizeof(consonants[0]);
// const int num_vowels = sizeof(vowels) / sizeof(vowels[0]);

// char* generateRandomName(int length) {
//     char* name = (char*)malloc(length + 1);
//     name[0] ='\0';

//     for (int i = 0; i < length; i++) {
//         if (i % 2 == 0) {
//             char* consonant = (char*)consonants[rand() % num_consonants];
//             strncat(name, consonant, length + 1 - strlen(name));
//         } else {
//             char* vowel = (char*)vowels[rand() % num_vowels];
//             strncat(name, vowel, length + 1 - strlen(name));
//         }
//     }
//     name[0] = name[0] - 32;
//     name[length] = '\0';
//     return name;
// }

char* generateRandomName() {
    char* nameList[] = {"Александр", "Анастасия", "Дмитрий", "Екатерина", "Максим", "Елена", "Артем", 
        "Мария", "Никита", "Ольга", "Андрей", "Наталья", "Сергей", "Ирина", "Владимир", "Татьяна", "Павел",
        "Юлия", "Иван", "Светлана", "Кирилл", "Ксения", "Михаил", "Анна", "Денис", "Виктория", "Роман", "Алёна",
        "Антон", "Валерия", "Глеб", "Полина", "Евгений", "Дарья", "Илья", "София", "Леонид", "Вероника", "Матвей",
        "Алина", "Николай", "Диана", "Петр", "Маргарита", "Станислав", "Карина", "Тимофей", "Елизавета", "Ярослав",
        "Кристина", "Вадим", "Александра", "Борис", "Надежда", "Виталий", "Людмила", "Георгий", "Регина", "Захар",
        "Василиса", "Константин", "Агата", "Лев", "Ангелина", "Руслан", "Варвара", "Степан", "Есения", "Арсений",
        "Злата", "Фёдор", "Милана", "Эдуард", "Ульяна", "Яков", "Влада", "Макар", "Альбина", "Савелий", "Арина",
        "Тимур", "Белла", "Даниил", "Валентина", "Эмиль", "Галина", "Григорий", "Доминика", "Игорь", "Ева",
        "Леонид", "Жанна", "Мирон", "Зарина", "Олег", "Инна", "Платон", "Камилла", "Ростислав", "Лидия",
        "Самуил", "Майя", "Эльдар", "Нелли", "Юрий", "Оксана", "Ян", "Раиса"};
    int numNames = sizeof(nameList) / sizeof(nameList[0]);
    return nameList[rand() % numNames];
}

void hundredTenThousandAndHundredThousandTimeTest() {
    int nSmall = 100;
    int nMedium = 10000;
    int nBig = 100000;
    struct Student fewStudents[nSmall];
    struct Student manyStudents[nMedium];
    struct Student *shitloadStudents = malloc(nBig*sizeof(struct Student));
    clock_t start, end;
    double cpu_time_used;

    //selectSort
    for (int i = 0; i < nSmall; i++) {
        fewStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    selectSort(fewStudents, nSmall);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы SelectSort 100: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nSmall*sizeof(struct Student));

    for (int i = 0; i < nMedium; i++) {
        manyStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    selectSort(manyStudents, nMedium);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы SelectSort 10000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nMedium*sizeof(struct Student));

    for (int i = 0; i < nBig; i++) {
        shitloadStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    selectSort(shitloadStudents, nBig);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы SelectSort 100000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nBig*sizeof(struct Student));

    //insertSort
    for (int i = 0; i < nSmall; i++) {
        fewStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    insertSort(fewStudents, nSmall);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы InsertSort 100: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nSmall*sizeof(struct Student));

    for (int i = 0; i < nMedium; i++) {
        manyStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    insertSort(manyStudents, nMedium);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы InsertSort 10000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nMedium*sizeof(struct Student));

    for (int i = 0; i < nBig; i++) {
        shitloadStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    insertSort(shitloadStudents, nBig);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы InsertSort 100000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nBig*sizeof(struct Student));

    //shellSort
    for (int i = 0; i < nSmall; i++) {
        fewStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    shellSort(fewStudents, nSmall);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы ShellSort 100: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nSmall*sizeof(struct Student));

    for (int i = 0; i < nMedium; i++) {
        manyStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    shellSort(manyStudents, nMedium);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы ShellSort 10000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nMedium*sizeof(struct Student));

    for (int i = 0; i < nBig; i++) {
        shitloadStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    shellSort(shitloadStudents, nBig);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы ShellSort 100000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nBig*sizeof(struct Student));

    //Counting Sort
    for (int i = 0; i < nSmall; i++) {
        fewStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    countingSort(fewStudents, nSmall);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы CountingSort 100: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nSmall*sizeof(struct Student));

    for (int i = 0; i < nMedium; i++) {
        manyStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    countingSort(manyStudents, nMedium);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы CountingSort 10000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nMedium*sizeof(struct Student));

    for (int i = 0; i < nBig; i++) {
        shitloadStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    countingSort(shitloadStudents, nBig);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы CountingSort 100000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nBig*sizeof(struct Student));

    //Quick Sort
    for (int i = 0; i < nSmall; i++) {
        fewStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    quickSort(fewStudents, 0, nSmall - 1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы QuickSort 100: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nSmall*sizeof(struct Student));

    for (int i = 0; i < nMedium; i++) {
        manyStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    quickSort(manyStudents, 0, nMedium - 1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы QuickSort 10000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nMedium*sizeof(struct Student));

    for (int i = 0; i < nBig; i++) {
        shitloadStudents[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    }
    start = clock();
    quickSort(shitloadStudents, 0, nBig - 1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время работы QuickSort 100000: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , nBig*sizeof(struct Student));

    free(shitloadStudents);
}

void printCPUInfo() {
    printf("Модель процессора:\n");
    system("grep 'model name' /proc/cpuinfo | head -n 1 | awk -F: '{print $2}' | sed 's/^ //g'");

    printf("\nЧастота процессора:\n");
    system("grep 'cpu MHz' /proc/cpuinfo | head -n 1 | awk -F: '{print $2}' | sed 's/^ //g'");
}

void main() {
    srand(time(NULL));
    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();
    // struct Student *students = malloc(N*sizeof(struct Student));
    // for (int i = 0; i < N; i++) {
    //     students[i] = addStudent(generateRandomName(), rand() % 101, rand() % 101, rand() % 101);
    //     // printStudentInfo(students[i]);
    // }
    // hundredTenThousandAndHundredThousandTimeTest();
    // quickSort(students, 0, N - 1);
    // // printf("\n------------------------------Sorted------------------------------\n\n");
    // // for (int i = 0; i < N; i++) {
    // //     printStudentInfo(students[i]);
    // // }
    // free(students);
    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("Время работы процессора: %f секунд\nРазмер данных: %ld байт\n\n" , cpu_time_used , N*sizeof(struct Student));
    // printCPUInfo();
    system("wmic cpu get name,maxlockspeed");
}
