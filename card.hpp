#pragma once

#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLACK   "\033[30m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

typedef enum {
    NONE,
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
} CardType;

typedef struct Card_t {
    CardType type;
    int value;

    static std::string ReturnString(CardType type);
    static std::string ReturnColor(CardType type);
    static std::string ReturnCardValueString(int value);
    static void PrintCard(struct Card_t card);

} Card;


