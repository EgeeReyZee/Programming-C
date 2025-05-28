#include <stdio.h>
#include "functions.h"

void clear_input_buffer(void);

int main(void) {
    printf("\033[1;34mДобро пожаловать в игру 'Сундук'!\033[0m\n");
    char yorn;
    printf("Хотите прочитать правила игры? [Y/n] ");
    scanf(" %c", &yorn);
    clear_input_buffer();

    if (yorn == 'Y' || yorn == 'y') {
        printf("\033[1;34mСуть игры 'Сундук' заключается в том, чтобы собрать как можно больше сундуков\033[0m\n");
        printf("\033[1;34mСундук это 4 карты одного номинала всех мастей\033[0m\n");
        printf("\033[1;31mНапример: 6♥️ 6♦️ 6♣️ 6♠️\033[0m\n");
        printf("\033[1;34mВы можете спросить у любого игрока о наличии у него интересующей вас карты\033[0m\n");
        printf("\033[1;34mНо только если у вас есть карта того же номинала\033[0m\n");
        printf("\033[1;34mЕсли у него есть, то он отдает вам эту карту и ваш ход продолжается\033[0m\n");
        printf("\033[1;34mЕсли нет, то вы вытягиваете карту из колоды\033[0m\n");
        printf("\033[1;34mИзначально у всех по 5 карт\033[0m\n");
        printf("\033[1;32mКаждый сундук дает по одному очку\033[0m\n");
        printf("\033[1;32mПобеждает тот, у кого больше всего сундуков\033[0m\n");
    } else {
        printf("\033[1;32mУдачи!\033[0m\n");
    }

    do {
        printf("Введите количество ботов (2-6): ");
        if (scanf("%d", &num_bots) != 1) {
            printf("Неверный ввод. Пожалуйста, введите число от 2 до 6.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
    } while (num_bots < 2 || num_bots > 6);

    num_players = num_bots + 1;

    players[0].is_bot = false;
    players[0].chests = 0;
    players[0].hand_size = 0;
    players[0].color = 0;

    for (int i = 1; i < num_players; i++) {
        players[i].is_bot = true;
        players[i].chests = 0;
        players[i].hand_size = 0;
        players[i].color = i;
    }

    init_deck();
    shuffle_deck();
    deal_cards();

    game_loop();

    return 0;
}
