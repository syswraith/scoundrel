#include <iostream>
#include "../include/room.hpp"

void Room::Load()
{
    for (int i = 0; i < 4; i++)
        room[i] = deck.PopDeck();
}


void Room::Run()
{
    // when running, the cards are picked up 
    // and placed at the end of the deck
    // and then the cards are refilled in the room
    // running is allowed only once
    // and not when once the cards are picked
    
    if (Room::hasRun) {
        std::cout << "Can't run more than once.\n";
        return;
    }
    
    Room::hasRun = true;
    for (int i = 0; i < 4; i++) {
        deck.PushDeck(room[i]);
        room[i] = {NONE, 0};
    }

    Load();

}

void Room::LoadNext()
{
    // base case: if cardsLeft == 1
    // then load new cards into the thing
    // minus the one card thats left
    
    for (int i = 0; i < 4; i++) {
        if (room[i].type == NONE) {
            room[i] = deck.PopDeck();
            cardsLeft++;
        }
    }
}

void Room::Print()
{
    for (int i = 0; i < 4; i++)
    {
        if (room[i].type == NONE) continue;
        Card::Print(room[i]);
        std::cout << '\n';
    }
}

Room::Room(Deck &deck_ref) : deck(deck_ref)
{

    Room::hasRun = false;
    Room::cardsLeft = 4;
    Load();
};
