#pragma once

#include "card.hpp"

struct Player 
{

  static constexpr int maxHealth = 20;

  int health;
  Card weapon;
  bool isDead;
  Card monsterStack[44];
  int monsterStackCount{};

  Player();

  ~Player() {}

    void Print();
    void DecreaseHealth(int damage);
    void AttackBare(const Card &card);
    void AttackWeapon(const Card &card);
    void IncreaseHealth(int restore);
    void EquipWeapon(const Card &card);
    void DrinkPotion(const Card &card);


    void PushMonster(const Card &card);
    void DiscardMonsters();


};
