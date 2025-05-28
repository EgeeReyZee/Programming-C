#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

#define MAX_PLAYERS 7
#define INIT_HAND_SIZE 5
#define DECK_SIZE 52
#define NUM_RANKS 13
#define NUM_SUITS 4

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

extern const char* colors[];
extern const char* reset_color;
extern const char* suits[];
extern const char* ranks[];

extern Deck deck;
extern Player players[MAX_PLAYERS];
extern int num_players;
extern int num_bots;

void init_deck(void);
void shuffle_deck(void);
void deal_cards(void);

bool has_card(Player *player, int rank, int suit);
bool has_rank(Player *player, int rank);

void transfer_card(Player *from, Player *to, int rank, int suit);
void check_chest(Player *player);

void print_player_cards(Player *player);
void print_available_ranks(Player *player);

void clear_input_buffer(void);
int get_valid_input(int min, int max);

void bot_turn(int bot_index);
void game_loop(void);

#endif
