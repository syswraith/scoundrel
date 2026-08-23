#include "../include/card.hpp"
#include <iostream>
#include <string>

std::string Card::ReturnString(CardType type)
{
    switch(type) {
        case CLUBS:
            return "♣";
        case DIAMONDS:
            return "♦";
        case HEARTS:
            return "♥";
        case SPADES:
            return "♠";
        case NONE:
            return "?";
    }

    return "?";
}

std::string Card::ReturnColor(CardType type)
{
    switch(type) {
        case DIAMONDS:
        case HEARTS:
            return RED;
        case CLUBS:
        case SPADES:
            return GREEN;
        case NONE:
            return RESET;
    }

    return RESET;
}

std::string Card::ReturnCardValueString(int value)
{

    switch(value) {
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        case 14: return "A"; 
        default: return std::to_string(value);

    }

}

void Card::Print(Card card)
{
    if (card.type != NONE) {
        std::cout << ReturnColor(card.type) << ReturnString(card.type) << ReturnCardValueString(card.value) << RESET;
    }
}


