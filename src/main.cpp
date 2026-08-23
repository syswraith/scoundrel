#include <iostream>

#include "../include/deck.hpp"
#include "../include/room.hpp"
#include "../include/player.hpp"

int main(void)
{

    Deck deck;
    Room room(deck);
    Player player;


    room.Print();

    while (!player.isDead)
    {
        int choice{};
        std::cout << "Pick card: ";
        std::cin >> choice;

        player.Pick(room.room[choice]);
        room.cardsLeft--;

        if (room.cardsLeft == 1)
            room.LoadNext();

        player.Print();
        room.Print();
    }

    if (player.isDead) {
        std::cout << "Player has died\n";
    } else {
        std::cout << "Player has won\n";
    }

    return 0;
}
