#include "../include/deck.hpp"
#include "../include/player.hpp"
#include <iostream>

int main(void)
{
    Card room[4]{};

    Deck deck;
    Player player;

    for (int i = 0; i < 44; i++) {
        Card card = deck.PopDeck();
        std::cout << i << " ";
        Card::PrintCard(card);
    }

    player.EquipWeapon(Card{DIAMONDS, 10});
    player.AttackWeapon(Card{SPADES, 10});

    player.PrintStats();


//    EquipWeapon((Card){.type = DIAMONDS, .value = 10});
//
//    AttackWeapon((Card){.type = SPADES, .value = 14});
//    AttackWeapon((Card){.type = SPADES, .value = 10});
//    AttackWeapon((Card){.type = SPADES, .value = 9});
//
//    DrinkPotion( (Card){.type = HEARTS, .value = 14} );
//
//    PrintStats();
//
//    std::cout << "Player has died!\n";
//    PrintStats();

    return 0;
}
