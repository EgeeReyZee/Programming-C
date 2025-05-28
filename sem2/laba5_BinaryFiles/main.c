#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// gcc binary.c -o binary
// ./binary bin.pcm

#define N 10

typedef struct Work {
    char name[128];
    int salary;
    char number[20];
}Work;

char* generateRandomName() {
    char* surnameList[] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", 
        "Martinez", "Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", 
        "White", "Harris", "Martin", "Thompson", "Garcia", "Wood", "Lewis", "Hill", "Roberts", "Green", "Clark", 
        "Walker", "Perez", "Hall", "Young", "Allen", "Wright", "King", "Scott", "Adams", "Baker", "Nelson", "Carter", 
        "Mitchell", "Roberts", "Turner", "Phillips", "Campbell", "Parker", "Evans", "Edwards", "Collins", "Stewart", 
        "Sanchez", "Morris", "Rogers", "Reed", "Cook", "Morgan", "Bell", "Murphy", "Bailey", "Rivera", "Cooper", 
        "Richardson", "Cox", "Howard", "Ward", "Torres", "Peterson", "Gray", "Ramirez", "James", "Watson", "Brooks", 
        "Kelly", "Sanders", "Price", "Bennett", "Woodward", "Barnes", "Ross", "Henderson", "Coleman", "Jenkins", "Perry", 
        "Powell", "Long", "Patterson", "Hughes", "Flores", "Washington", "Butler", "Simmons", "Foster", "Hayes"};
    char* nameList[] = {"Liam", "Noah", "Oliver", "Elijah", "James", "William", "Benjamin", "Lucas", "Henry", 
        "Theodore", "Owen", "Ethan", "Jackson", "Daniel", "Matthew", "Joseph", "Samuel", "David", "John", "Michael", 
        "Arthur", "Jasper", "Silas", "Atticus", "Finnian", "Felix", "Caspian", "Asher", "Rhys", "Rowan", "Declan", "Callum", 
        "Levi", "Micah", "Gabriel", "Julian", "Vincent", "Dominic", "Walter", "George", "Oscar", "Charles", "Olivia", "Emma", 
        "Charlotte", "Amelia", "Sophia", "Isabella", "Ava", "Mia", "Evelyn", "Luna", "Harper", "Elizabeth", "Emily", "Abigail", 
        "Ella", "Avery", "Sofia", "Chloe", "Victoria", "Madison", "Aurora", "Hazel", "Willow", "Adeline", "Eloise", "Imogen", 
        "Violet", "Scarlett", "Beatrice", "Alice", "Genevieve", "Florence", "Clara", "Eleanor", "Grace", "Lillian", "Nora", 
        "Stella", "Ivy", "Piper", "Rose", "Riley", "Jordan", "Skyler", "Quinn", "Blake", "River", "Phoenix", "Sage", 
        "Charlie", "Emerson", "Dakota", "Jamie", "Jesse"};
    int numName = sizeof(nameList) / sizeof(nameList[0]);
    int numSurname = sizeof(surnameList) / sizeof(surnameList[0]);
    char *fullName = (char *)malloc(128*sizeof(char));
    // char fullName[128];
    snprintf(fullName, 128, "%s %s %s", nameList[rand() % numName], nameList[rand() % numName], surnameList[rand() % numSurname]);
    return fullName;
}

char *generateRandomNumber() {
    char *number = (char *)malloc(20*sizeof(char));
    // char number[20];
    snprintf(number, 20, "+7 (%d) %d-%d-%d", (rand() % 100) + 900, (rand() % 900) + 100, (rand() % 90) + 10, (rand() % 90) + 10);
    return number;
}

void search(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    int choice;
    printf("\nПо какому полю выполнить поиск?\n1 - ФИО\n2 - Зарплата\n3 - Номер\n");
    scanf("%d", &choice);   

    char searchStr[64];
    int searchSal;
    char searchNum[20];
    Work s;
    int found = 0;

    switch (choice) {
        case 1:
            printf("Введите ФИО: ");
            getchar();
            fgets(searchStr, sizeof(searchStr), stdin);
            searchStr[strcspn(searchStr, "\n")] = '\0';
            break;
        case 2:
            printf("Введите ЗП: ");
            scanf("%d", &searchSal);
            break;
        case 3:
            printf("Введите номер: ");
            getchar();
            fgets(searchNum, sizeof(searchNum), stdin);
            searchNum[strcspn(searchNum, "\n")] = '\0';
            break;
        default:
            printf("Неверный выбор.\n");
            fclose(file);
            return;
    }

    while (fread(&s, sizeof(Work), 1,file) == 1) {
            int match = 0;
            switch (choice) {
                case 1:
                    if (strcmp(s.name, searchStr) == 0) match = 1;
                    break;
                case 2:
                    if (s.salary == searchSal) match = 1;
                    break;
                case 3:
                    if (strcmp(s.number, searchNum) == 0) match = 1;
                    break;
            }
            if (match == 1) {
                printf("%-40s %-20d %-20s\n", s.name, s.salary, s.number);
                found = 1;
            
        }
    
    

    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc < 2) {
        printf("Usage: ./executable bin.pcm\n");
        exit(1);
    }

    FILE *file = fopen(argv[1], "wb");
    if (file == NULL) {
        printf("In %s:%d Error opening file\n", __FILE__, __LINE__);
        exit(1);
    }

    Work array[N];
    printf("Writing to binary file..\n");
    for (int i = 0; i < N; i++) {
        strncpy(array[i].name, generateRandomName(), sizeof(array[i].name) - 1);
        array[i].name[sizeof(array[i].name) - 1] = '\0';

        array[i].salary = (rand() % 1000000) + 20000;

        strncpy(array[i].number, generateRandomNumber(), sizeof(array[i].number) - 1);
        array[i].number[sizeof(array[i].number) - 1] = '\0';

        // Запись по одной структуре за раз
        printf("[%d] name %s salary %d number %s\n", i, array[i].name, array[i].salary, array[i].number);
        fwrite(&array[i], sizeof(Work), 1, file); 
        
    }

    memset(array, 0, sizeof(*array));


    fclose(file);
    printf("Done.\n");

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("In %s:%d Error opening file\n", __FILE__, __LINE__);
        exit(1);
    }
    printf("Reading from binary file..\n");
    // читаем одной строкой из бинарного файла N раз sizeof(struct some_data)
    fread(array, sizeof(Work), N, file);
    search(argv[1]);

    fclose(file);

}
