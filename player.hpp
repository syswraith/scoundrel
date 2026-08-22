#pragma once

#include "card.hpp"

class Player 
{

    static constexpr int maxHealth = 20;

public:
  int health;
  Card weapon;
  bool isDead;
  Card monsterStack[44];
  int monsterStackCount{};

  Player() 
  {
    this->health = maxHealth;
    this->weapon = (Card){CLUBS, 10};
    this->isDead = false;
  }

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
