#include <stdio.h>
#include <string.h>

void main() {
  char text[3000];
  char max_word[100];
  int max_cnt = 0;
  int cur_cnt = 0;

  printf("Введите текст: ");
  fgets(text, 1000, stdin);

  char *word = strtok(text, " \t\n");
  while (word != NULL) {
    cur_cnt = 0;
    for (int i = 0; i < strlen(word); i++) {
      if (word[i] == 'c') {
        cur_cnt++;
      }
    }
    if (cur_cnt > max_cnt) {
      max_cnt = cur_cnt;
      strcpy(max_word, word);
    }
    word = strtok(NULL, " \t\n");
  }

  printf("Слово с максимальным количеством букв 'c': %s\n", max_word);
  printf("Количество букв 'c': %d\n", max_cnt);
}
