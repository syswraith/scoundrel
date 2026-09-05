#pragma once

#include "card.hpp"

struct Player 
{

  static constexpr int maxHealth = 20;

  int health;
  Card weapon;
  bool isDead;
  bool isBound;
  Card monsterStack[44];
  int monsterStackCount{};
  int potionsPerRoom{};
  static constexpr int maxPotionsPerRoom = 1;

  Player();

    void DecreaseHealth(int damage);
    void AttackWeapon(const Card &card);
    void AttackBare(const Card &card);
    void IncreaseHealth(int restore);
    void EquipWeapon(const Card &card);
    void DrinkPotion(const Card &card);
    void Pick(Card &card, bool bareFight = false);
    void ResetPotionsPerRoom();

    void PushMonster(const Card &card);

};
