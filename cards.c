#include <stdio.h>

#include "cards.h"

typedef enum {
    CLUBS, 
    DIAMONDS,
    HEARTS,
    SPADES
} Suit;

typedef enum {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} Rank;

typedef struct card {
    Suit suit;
    Rank rank;
} card_t;

card_t deck[DECK_SIZE];


int is_valid_card(Suit suit, Rank rank) {
    if (suit == HEARTS || suit == DIAMONDS) {
        switch(rank) {
            case ACE:
            case JACK:
            case QUEEN:
            case KING:
                return 0;
            default:
                return 1;
        }
    }
    
    return 1;

}

int initialise_deck() {
    int deck_size = 0;

    for (int s = CLUBS; s <= SPADES; s++)
    {
        for (int r = ACE; r <= KING; r++) {
            if ( is_valid_card(s, r) ) {
                deck[deck_size].suit = s;
                deck[deck_size].rank = r;
                deck_size++;
            }
        }
    }
    
    return 0;
}