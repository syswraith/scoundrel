#pragma once

#include "../include/card.hpp"
#include "../include/deck.hpp"
#include <cstddef>

class Room {
    Deck &deck;
    void Load();
    bool hasRun;

    public:
    Card room[4];
    size_t cardsLeft;
    void LoadNext();
    void Run();
    void Print();
    Room(Deck &deck_ref);
};
