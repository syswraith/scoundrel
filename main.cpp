#include "deck.hpp"
#include <iostream>
#include <memory>

int main(void)
{
    Card room[4]{};

    std::unique_ptr<Deck> deck = std::make_unique<Deck>();

    for (int i = 0; i < 44; i++) {
        Card card = deck->PopDeck();
        std::cout << i << " ";
        Card::PrintCard(card);
    }


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
