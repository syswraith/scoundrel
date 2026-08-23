#pragma once

#include "../include/card.hpp"
#include "../include/deck.hpp"

class Room {
    Card room[4];
    Deck &deck;

    void Load();

    public:

    void Run();
    void Print();
    Room(Deck &deck_ref);

};
