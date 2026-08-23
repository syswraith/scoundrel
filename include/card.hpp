#pragma once

#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLACK   "\033[30m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

enum CardType {
    NONE,
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

struct Card {
    CardType type;
    int value;

    static std::string ReturnString(CardType type);
    static std::string ReturnColor(CardType type);
    static std::string ReturnCardValueString(int value);
    static void PrintCard(Card card);

};


