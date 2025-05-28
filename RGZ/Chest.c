#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_PLAYERS 7
#define INIT_HAND_SIZE 5
#define DECK_SIZE 52
#define NUM_RANKS 13
#define NUM_SUITS 4

const char* colors[] = {
    "\033[1;31m", "\033[1;32m", "\033[1;33m",
    "\033[1;34m", "\033[1;35m", "\033[1;36m", "\033[1;37m"
};
const char* reset_color = "\033[0m";

const char *suits[] = {"♥", "♦", "♣", "♠"};
const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

typedef struct {
    int rank;
    int suit;
} Card;

typedef struct {
    Card cards[DECK_SIZE];
    int top;
} Deck;

typedef struct {
    Card hand[DECK_SIZE];
    int hand_size;
    int chests;
    bool is_bot;
    int color;
} Player;

Deck deck;
Player players[MAX_PLAYERS];
int num_players = 0;
int num_bots = 0;

void init_deck() {
    int index = 0;
    for (int s = 0; s < NUM_SUITS; s++) {
        for (int r = 0; r < NUM_RANKS; r++) {
            deck.cards[index].rank = r;
            deck.cards[index].suit = s;
            index++;
        }
    }
    deck.top = 0;
}

void shuffle_deck() {
    srand(time(NULL));
    for (int i = 0; i < DECK_SIZE; i++) {
        int j = rand() % DECK_SIZE;
        Card temp = deck.cards[i];
        deck.cards[i] = deck.cards[j];
        deck.cards[j] = temp;
    }
}

void deal_cards() {
    for (int p = 0; p < num_players; p++) {
        for (int i = 0; i < INIT_HAND_SIZE; i++) {
            if (deck.top < DECK_SIZE) {
                players[p].hand[players[p].hand_size++] = deck.cards[deck.top++];
            }
        }
    }
}

bool has_card(Player *player, int rank, int suit) {
    for (int i = 0; i < player->hand_size; i++) {
        if (player->hand[i].rank == rank && player->hand[i].suit == suit) {
            return true;
        }
    }
    return false;
}

bool has_rank(Player *player, int rank) {
    for (int i = 0; i < player->hand_size; i++) {
        if (player->hand[i].rank == rank) {
            return true;
        }
    }
    return false;
}

void transfer_card(Player *from, Player *to, int rank, int suit) {
    for (int i = 0; i < from->hand_size; i++) {
        if (from->hand[i].rank == rank && from->hand[i].suit == suit) {
            to->hand[to->hand_size++] = from->hand[i];
            for (int j = i; j < from->hand_size - 1; j++) {
                from->hand[j] = from->hand[j + 1];
            }
            from->hand_size--;
            break;
        }
    }
}

void check_chest(Player *player) {
    int rank_counts[NUM_RANKS] = {0};
    for (int i = 0; i < player->hand_size; i++) {
        rank_counts[player->hand[i].rank]++;
    }
    
    for (int r = 0; r < NUM_RANKS; r++) {
        if (rank_counts[r] == 4) {
            player->chests++;
            int removed = 0;
            for (int i = 0; i < player->hand_size; i++) {
                if (player->hand[i].rank == r) {
                    for (int j = i; j < player->hand_size - 1; j++) {
                        player->hand[j] = player->hand[j + 1];
                    }
                    player->hand_size--;
                    i--;
                    removed++;
                    if (removed == 4) break;
                }
            }
            printf("%s%sИгрок %d%s собрал сундук из %s%s%s!\n", 
                  colors[player->color], player->is_bot ? "Бот " : "",
                  (int)(player - players) + 1, reset_color,
                  colors[player->color], ranks[r], reset_color);
        }
    }
}

void print_player_cards(Player *player) {
    printf("Доступные карты:\n");
    for (int i = 0; i < player->hand_size; i++) {
        printf("%d: %s%s%s %s%s%s\n", 
            i + 1,
            colors[player->color],
            suits[player->hand[i].suit],
            reset_color,
            colors[player->color],
            ranks[player->hand[i].rank],
            reset_color
        );
    }
}



void print_available_ranks(Player *player) {
    printf("Доступные номиналы в вашей руке:\n");
    int available_ranks[NUM_RANKS] = {0};
    for (int i = 0; i < player->hand_size; i++) {
        available_ranks[player->hand[i].rank] = 1;
    }

    for (int r = 0; r < NUM_RANKS; r++) {
        if (available_ranks[r]) {
            printf("%d - %s%s%s\n", 
                  r + 2,
                  colors[player->color],
                  ranks[r],
                  reset_color);
        }
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int get_valid_input(int min, int max) {
    int input;
    while (1) {
        if (scanf("%d", &input) != 1) {
            printf("Неверный ввод. Пожалуйста, введите число от %d до %d: ", min, max);
            clear_input_buffer();
            continue;
        }
        if (input >= min && input <= max) {
            clear_input_buffer();
            return input;
        }
        printf("Неверный диапазон. Пожалуйста, введите число от %d до %d: ", min, max);
        clear_input_buffer();
    }
}

void bot_turn(int bot_index) {
    Player *bot = &players[bot_index];
    sleep(1);
    
    printf("%sХод бота %d%s\n", colors[bot->color], bot_index + 1, reset_color);
    
    if (bot->hand_size == 0) {
        printf("%sУ бота %d нет карт. Ход пропускается.%s\n", 
              colors[bot->color], bot_index + 1, reset_color);
        return;
    }
    
    int rank_choice;
    do {
        rank_choice = rand() % NUM_RANKS;
    } while (!has_rank(bot, rank_choice));
    
    int suit_choice = rand() % NUM_SUITS;
    
    int target_player;
    do {
        target_player = rand() % num_players;
    } while (target_player == bot_index);
    
    printf("%sБот %d спрашивает у %s %d%s: есть ли %s%s %s%s?\n", 
           colors[bot->color],
           bot_index + 1, 
           players[target_player].is_bot ? "бота" : "игрока",
           target_player + 1,
           reset_color,
           colors[bot->color],
           suits[suit_choice],
           colors[bot->color],
           ranks[rank_choice],
           reset_color);
    
    if (has_card(&players[target_player], rank_choice, suit_choice)) {
        printf("%sОтвет: Да! Карта передается боту %d%s\n", 
              colors[bot->color], bot_index + 1, reset_color);
        transfer_card(&players[target_player], bot, rank_choice, suit_choice);
        check_chest(bot);
        bot_turn(bot_index);
    } else {
        printf("%sОтвет: Нет. Бот тянет карту из колоды.%s\n", 
              colors[bot->color], reset_color);
        if (deck.top < DECK_SIZE) {
            bot->hand[bot->hand_size++] = deck.cards[deck.top++];
        }
    }
}

void game_loop() {
    int current_player = 0;
    bool game_over = false;
    
    while (!game_over) {
        if (players[current_player].is_bot) {
            bot_turn(current_player);
        } else {
            printf("\n%s--- Ваш ход ---%s\n", colors[0], reset_color);
            print_player_cards(&players[current_player]);
            
            if (players[current_player].hand_size == 0) {
                printf("%sУ вас нет карт. Ход переходит дальше.%s\n", colors[0], reset_color);
                current_player = (current_player + 1) % num_players;
                continue;
            }
            
            print_available_ranks(&players[current_player]);
            printf("Выберите номинал карты (2-14): ");
            int rank_choice = get_valid_input(2, 14) - 2;
            
            if (!has_rank(&players[current_player], rank_choice)) {
                printf("У вас нет карт этого номинала!\n");
                continue;
            }
            
            printf("Выберите масть (1-♥️   2-♦️   3-♣️   4-♠️  ): ");
            int suit_choice = get_valid_input(1, 4) - 1;
            
            printf("Доступные игроки:\n");
            for (int i = 0; i < num_players; i++) {
                if (i != current_player) {
                    printf("%d - %s%s%d%s\n", 
                          i + 1,
                          colors[i],
                          players[i].is_bot ? "Бот " : "Игрок ",
                          i + 1,
                          reset_color);
                }
            }
            
            printf("У кого вы хотите спросить? (1-%d): ", num_players);
            int target_player = get_valid_input(1, num_players) - 1;
            
            if (target_player == current_player) {
                printf("Нельзя выбирать себя!\n");
                continue;
            }
            
            printf("%sВы спрашиваете у %s %d%s: есть ли %s%s %s%s?\n",
                  colors[current_player],
                  players[target_player].is_bot ? "бота" : "игрока",
                  target_player + 1,
                  reset_color,
                  colors[current_player],
                  suits[suit_choice],
                  colors[current_player],
                  ranks[rank_choice],
                  reset_color);
            
            if (has_card(&players[target_player], rank_choice, suit_choice)) {
                printf("%sОтвет: Да! Карта ваша!%s\n", colors[current_player], reset_color);
                transfer_card(&players[target_player], &players[current_player], rank_choice, suit_choice);
                check_chest(&players[current_player]);
                continue;
            } else {
                printf("%sОтвет: Нет. Вы тянете карту из колоды.%s\n", colors[current_player], reset_color);
                if (deck.top < DECK_SIZE) {
                    players[current_player].hand[players[current_player].hand_size++] = deck.cards[deck.top++];
                    printf("%sВы получили: %s%s %s%s%s\n", 
                          colors[current_player],
                          colors[current_player],
                          suits[players[current_player].hand[players[current_player].hand_size - 1].suit],
                          colors[current_player],
                          ranks[players[current_player].hand[players[current_player].hand_size - 1].rank],
                          reset_color);
                }
            }
        }
        
        int cards_left = 0;
        for (int i = 0; i < num_players; i++) {
            cards_left += players[i].hand_size;
        }
        cards_left += (DECK_SIZE - deck.top);
        
        if (cards_left < 4) {
            game_over = true;
        }
        
        current_player = (current_player + 1) % num_players;
    }
    
    printf("\n%s--- Игра окончена! ---%s\n", colors[0], reset_color);
    printf("%sВаши сундуки: %d%s\n", colors[0], players[0].chests, reset_color);
    for (int i = 1; i < num_players; i++) {
        printf("%sБот %d: %d сундуков%s\n", colors[i], i, players[i].chests, reset_color);
    }
    
    int max_chests = -1;
    int winner = -1;
    bool draw = false;
    
    for (int i = 0; i < num_players; i++) {
        if (players[i].chests > max_chests) {
            max_chests = players[i].chests;
            winner = i;
            draw = false;
        } else if (players[i].chests == max_chests) {
            draw = true;
        }
    }
    
    if (draw) {
        printf("%sНичья!%s\n", colors[0], reset_color);
    } else if (winner == 0) {
        printf("%sВы победили!%s\n", colors[0], reset_color);
    } else {
        printf("%sПобедил бот %d!%s\n", colors[winner], winner, reset_color);
    }
}

int main() {
    printf("\033[1;34mДобро пожаловать в игру 'Сундук'!\033[0m\n");
    char yorn;
    printf("Хотите прочитать правила игры? [Y/n]");
    scanf("%c", &yorn);
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
    }
    else {
        printf("\033[1;32mУдачи\033[0m\n");
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
