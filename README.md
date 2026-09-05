# Scoundrel

A terminal implementation of the single-player roguelike dungeon card game
*Scoundrel* by Zach Gage & Kurt Bieg (2011), built with FTXUI.

A standard 52-card deck (no jokers) represents a dungeon. Four cards are dealt
as a room; clear each room until the deck runs out. Survive without reaching
0 HP — **Score** is your remaining HP.

## Rules

- **Deck**: 52 cards — ♠♣♦♥ each 2–14. Cards are dealt into rooms of 4.
- **HP**: 20 max.
- **Room**: 4 cards. You may resolve cards freely; once only 1 card is left
  the room is clear and the deck fills the empty slots (the carried card is
  never resolved). When the deck is empty, clearing the last room wins.
- **Monsters** (♠♣): deal damage equal to their value.
- **Weapons** (♦): equip to fight with reduced damage. Guard =
  weapon value − total value of monsters killed with it (floor 0); damage =
  monster − guard. A weapon's kill stack resets when you equip a new one.
- **Barehanded**: against a monster you may fight with your bare hands,
  taking the monster's full damage (the magical conversion doesn't let you
  attack without a weapon).
- **Potions** (♥): heal face value, capped at 20. Maximum 1 per room, reset
  after each monster kill. Hearts drawn at the cap are discarded (no effect).
- **Retreat** (`R`): return all 4 visible cards to the bottom of the deck and
  deal a fresh room. Allowed once per turn; resolving a card re-enables it.

## Controls

| Key | Action |
|-----|--------|
| `1`–`4` | Pick/act on that card |
| `W` / `B` | Fight with weapon / barehanded (when a fight choice is shown) |
| `Q` | Cancel a fight choice, or quit |
| `R` | Retreat / skip the room |

## Build

```sh
cmake -S . -B build
cmake --build build
./build/main
```

Requires C++20, CMake, and FTXUI (tested on Linux).