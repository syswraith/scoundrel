#include <iostream>
#include "../include/deck.hpp"
#include "../include/room.hpp"

int main(void)
{

    Deck deck;

    Room room(deck);

    std::cout << deck.Size() << '\n';
    room.Print();
    room.Run();
    std::cout << deck.Size() << '\n';
    room.Print();

    //Player player;

    //player.EquipWeapon(Card{DIAMONDS, 10});
    //player.AttackWeapon(Card{SPADES, 10});

    //player.Print();

    return 0;
}
