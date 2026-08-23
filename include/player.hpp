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

    void PrintStats();
    void DecreaseHealth(int damage);
    void AttackBare(Card card);
    void AttackWeapon(Card card);
    void IncreaseHealth(int restore);
    void EquipWeapon(Card card);
    void DrinkPotion(Card card);


    void PushMonster(Card card);
    void DiscardMonsters();


};
