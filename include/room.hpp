#pragma once

#include "../include/card.hpp"
#include "../include/deck.hpp"
#include <cstddef>
#include <vector>

class Room {
    Deck &deck;
    void Load();

    public:
    Card room[4];
    size_t cardsLeft;
    bool isComplete;
    void LoadNext();
    void Run();
    Room(Deck &deck_ref);
};
