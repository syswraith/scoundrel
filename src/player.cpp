#include "../include/player.hpp"
#include <algorithm>

void Player::DecreaseHealth(int damage)
{
    this->health = std::max(0, this->health - damage);

    if (this->health <= 0) {
        this->isDead = true;
    }
}

void Player::AttackWeapon(const Card &card)
{
    // Without a weapon the player takes the monster's full value.
    if (this->weapon.type == NONE) {
        DecreaseHealth(static_cast<int>(card.value));
        return;
    }

    // Every monster previously defeated with this weapon drains its
    // effectiveness: effective = weapon value - total stack value.
    int totalStack = 0;
    for (int i = 0; i < this->monsterStackCount; i++)
        totalStack += static_cast<int>(this->monsterStack[i].value);

    int effectiveWeapon = static_cast<int>(this->weapon.value) - totalStack;
    int damage = static_cast<int>(card.value) - effectiveWeapon;
    if (damage < 0)
        damage = 0;

    DecreaseHealth(damage);

    this->isBound = true;
    PushMonster(card);
}

void Player::AttackBare(const Card &card)
{
    DecreaseHealth(static_cast<int>(card.value));
}

void Player::IncreaseHealth(int restore)
{
    if (this->health >= Player::maxHealth)
        return;

    this->health = std::min(this->health + restore, Player::maxHealth);
}

void Player::EquipWeapon(const Card &card)
{
    if (card.type != DIAMONDS)
        return;

    this->weapon = card;
    this->isBound = false;
    this->monsterStackCount = 0;
}

void Player::DrinkPotion(const Card &card)
{
    if (potionsPerRoom >= maxPotionsPerRoom)
        return;
    potionsPerRoom++;
    IncreaseHealth(static_cast<int>(card.value));
}

void Player::ResetPotionsPerRoom()
{
    potionsPerRoom = 0;
}

void Player::PushMonster(const Card &card)
{
    this->monsterStack[this->monsterStackCount++] = card;
}

void Player::Pick(Card &card, bool bareFight)
{
    switch (card.type) {
        case DIAMONDS:
            Player::EquipWeapon(card);
            break;
        case HEARTS:
            Player::DrinkPotion(card);
            break;
        case SPADES:
        case CLUBS:
            if (bareFight)
                Player::AttackBare(card);
            else
                Player::AttackWeapon(card);
            ResetPotionsPerRoom();
            break;
        case NONE:
            break;
    }

    card = Card {NONE, 0};
}

Player::Player()
{
    this->health = maxHealth;
    this->weapon = Card{NONE, 0};
    this->isDead = false;
    this->isBound = false;
    this->potionsPerRoom = 0;
}