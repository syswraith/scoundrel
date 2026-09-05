#include "../include/room.hpp"

void Room::Load()
{
    for (int i = 0; i < 4; i++)
        room[i] = deck.PopDeck();
    cardsLeft = 4;
    isComplete = false;
}

void Room::Run()
{
    // All visible cards return to the bottom of the deck, then a new
    // room is dealt.
    for (int i = 0; i < 4; i++) {
        if (room[i].type != NONE)
            deck.PushDeck(room[i]);
        room[i] = {NONE, 0};
    }
    cardsLeft = 0;

    // Draw a new room of four cards.
    for (int i = 0; i < 4; i++) {
        Card c = deck.PopDeck();
        room[i] = c;
        if (c.type != NONE)
            cardsLeft++;
    }
    isComplete = (cardsLeft <= 1);
}

void Room::LoadNext()
{
    for (int i = 0; i < 4; i++) {
        if (room[i].type == NONE) {
            Card c = deck.PopDeck();
            room[i] = c;
            if (c.type != NONE)
                cardsLeft++;
        }
    }
    isComplete = false;
}

Room::Room(Deck &deck_ref) : deck(deck_ref)
{
    cardsLeft = 0;
    isComplete = false;
    Load();
}