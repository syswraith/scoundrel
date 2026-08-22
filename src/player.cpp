#include "../include/player.hpp"
#include "../include/card.hpp"
#include <algorithm>
#include <iostream>


void Player::PrintStats()
{
    std::cout << "Player stats:\n";
    std::cout << "Health: " << this->health << '\n';

    std::cout << "Weapon: " << Card::ReturnColor(this->weapon.type) << Card::ReturnString(this->weapon.type) << this->weapon.value << RESET << '\n';
 

    if (!this->monsterStackCount) {
        std::cout << "No monsters.\n";
        return;
    }

   std::cout << "Monster stack:\n";

    for (int i = 0; i < this->monsterStackCount; i++) {
        Card::PrintCard(this->monsterStack[i]);
    }
}



void Player::DecreaseHealth(int damage)
{
    this->health -= damage;

    if (this->health <= 0) {
        this->isDead = true;
    }
}

void Player::AttackBare(Card card)
{
    DecreaseHealth(card.value);
    std::cout << "Player attacked bare-handed!\n";
}

void Player::AttackWeapon(Card card)
{
    Card::PrintCard(card);

    int damage = card.value;
    int weaponDamage = this->weapon.value;
    int damageLeft = 0;

    if (this->monsterStackCount == 0) {
        damageLeft = damage - weaponDamage;
    } else {
        int topCard = this->monsterStack[this->monsterStackCount - 1].value;
        if (topCard > damage) {
            damageLeft = damage - weaponDamage;
        } else {
            std::cout << YELLOW << "Can't damage!" << RESET << '\n';
            return;
        }
    }

    if (damageLeft > 0) {
        DecreaseHealth(damageLeft);
    }

    PushMonster(card);
}

void Player::IncreaseHealth(int restore)
{
    if (this->health >= Player::maxHealth) {
        std::cout << YELLOW << "Player has max health!" << RESET << '\n';
        return;
    }

    this->health = std::min(this->health + restore, Player::maxHealth);
}

void Player::EquipWeapon(Card card)
{
    this->weapon = card;
}

void Player::DrinkPotion(Card card)
{
    IncreaseHealth(card.value);
}


void Player::PushMonster(Card card)
{
    this->monsterStack[this->monsterStackCount++] = card;
}

void Player::DiscardMonsters()
{
    this->monsterStackCount = 0;
}


