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

    for (int i = 0; i < 4; i++) {
        deck.PushDeck(room[i]);
        room[i] = {NONE, 0};
    }

    Load();

}

void Room::Print()
{
    for (int i = 0; i < 4; i++)
        Card::Print(room[i]);
}

Room::Room(Deck &deck_ref) : deck(deck_ref)
{
    Load();
};
