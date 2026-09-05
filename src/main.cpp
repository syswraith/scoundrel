#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

#include "../include/deck.hpp"
#include "../include/room.hpp"
#include "../include/player.hpp"

using namespace ftxui;

struct GameState {
    Deck deck;
    Room room;
    Player player;
    bool gameOver = false;
    bool won = false;
    bool hasRunThisTurn = false;
    int fightSlot = -1;
    int discardCount = 0;

    GameState() : room(deck) {}
};

// ── Helpers ──────────────────────────────────────────────────

std::string Symbol(CardType type) {
    switch (type) {
        case CLUBS:    return "\u2663";
        case DIAMONDS: return "\u2666";
        case HEARTS:   return "\u2665";
        case SPADES:   return "\u2660";
        default:       return "?";
    }
}

std::string RankStr(int value) {
    switch (value) {
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        case 14: return "A";
        default: return std::to_string(value);
    }
}

std::string ShortLabel(const Card& c) {
    if (c.type == NONE) return "--";
    return Symbol(c.type) + " " + RankStr(c.value);
}

// Semantic colors: hearts=green (healing), enemies=red (danger), diamonds=yellow (weapon)
Color SemanticColor(CardType type) {
    switch (type) {
        case HEARTS:   return Color::Green;
        case DIAMONDS: return Color::Yellow;
        case CLUBS:
        case SPADES:   return Color::Red;
        default:       return Color::White;
    }
}

Color HealthColor(int hp) {
    if (hp > 14) return Color::Green;
    if (hp > 7)  return Color::Yellow;
    return Color::Red;
}

std::string ActionVerb(CardType type) {
    switch (type) {
        case SPADES:
        case CLUBS:    return "Fight";
        case HEARTS:   return "Drink";
        case DIAMONDS: return "Equip";
        default:       return "???";
    }
}

std::string ActionVerb(const Card& c, bool potionLimitHit) {
    if (c.type == HEARTS && potionLimitHit)
        return "Discard";
    return ActionVerb(c.type);
}

// ── Card Rendering ───────────────────────────────────────────

Element RenderCard(const Card& card) {
    if (card.type == NONE) {
        return vbox({
            text("┌─────────┐") | dim,
            text("│         │") | dim,
            text("│  empty  │") | dim,
            text("│         │") | dim,
            text("└─────────┘") | dim,
        });
    }

    Color c = SemanticColor(card.type);
    std::string sym = Symbol(card.type);
    std::string val = RankStr(card.value);
    std::string tail = val.size() == 1 ? "   " : "  ";

    return vbox({
        text("┌─────────┐") | color(c),
        text("\u2502   " + sym + " " + val + tail + "\u2502") | color(c),
        text("\u2502         \u2502") | color(c),
        text("\u2502   " + val + " " + sym + tail + "\u2502") | color(c) | bold,
        text("└─────────┘") | color(c),
    });
}

// ── Player Panel ─────────────────────────────────────────────

Element BuildPlayerPanel(GameState& state) {
    Elements p;
    p.push_back(text(""));
    p.push_back(text(" PLAYER") | bold | color(Color::Cyan));
    p.push_back(hbox({
        text("  Health ") | color(Color::GrayDark),
        text(std::to_string(state.player.health) + "/" + std::to_string(Player::maxHealth))
            | color(HealthColor(state.player.health)) | bold,
    }));
    p.push_back(text(""));
    p.push_back(hbox({
        text("  Deck  ") | color(Color::GrayDark),
        text(std::to_string(state.deck.Size()) + " left") | color(Color::White),
    }));
    p.push_back(hbox({
        text("  Disc  ") | color(Color::GrayDark),
        text(std::to_string(state.discardCount)) | color(Color::GrayDark),
    }));
    p.push_back(text(""));

    return vbox(p) | border | color(Color::GrayDark) | size(WIDTH, GREATER_THAN, 38);
}

// ── Status Panel ─────────────────────────────────────────────

Element BuildStatusPanel(GameState& state) {
    Elements p;
    p.push_back(text(""));
    p.push_back(text(" STATUS") | bold | color(Color::Cyan));

    if (state.player.weapon.type != NONE) {
        int totalStack = 0;
        for (int i = 0; i < state.player.monsterStackCount; i++)
            totalStack += static_cast<int>(state.player.monsterStack[i].value);
        int guard = state.player.weapon.value - totalStack;
        if (guard < 0) guard = 0;

        std::string bound = state.player.isBound ? " [BOUND]" : "";
        p.push_back(hbox({
            text("  Weapon ") | color(Color::GrayDark),
            text(ShortLabel(state.player.weapon)) | color(Color::Yellow) | bold,
        }));
        p.push_back(hbox({
            text("  Guard ") | color(Color::GrayDark),
            text(std::to_string(guard)) | color(Color::White),
            text(bound) | color(Color::Yellow) | dim,
        }));
    } else {
        p.push_back(hbox({
            text("  Weapon ") | color(Color::GrayDark),
            text("none") | color(Color::GrayDark) | dim,
        }));
    }

    p.push_back(hbox({
        text("  Potion ") | color(Color::GrayDark),
        text(std::to_string(state.player.potionsPerRoom) + "/" + std::to_string(Player::maxPotionsPerRoom))
            | color(Color::White),
    }));
    p.push_back(text(""));

    return vbox(p) | border | color(Color::GrayDark) | size(WIDTH, GREATER_THAN, 38);
}

// ── Action Bar ───────────────────────────────────────────────

Element BuildActionBar(GameState& state) {
    Elements row;
    for (int i = 0; i < 4; i++) {
        Card& c = state.room.room[i];
        std::string n = "[" + std::to_string(i + 1) + "]";

        if (c.type == NONE) {
            row.push_back(text(n + " --") | dim | color(Color::GrayDark));
        } else {
            bool limit = c.type == HEARTS &&
                state.player.potionsPerRoom >= Player::maxPotionsPerRoom;
            row.push_back(hbox({
                text(n + " ") | color(Color::Cyan),
                text(ActionVerb(c, limit) + " ") | color(Color::Cyan),
                text(ShortLabel(c)) | color(SemanticColor(c.type)) | bold,
            }));
        }
    }

    Elements rowJoined;
    for (size_t i = 0; i < row.size(); i++) {
        if (i) rowJoined.push_back(text("   ") | color(Color::GrayDark));
        rowJoined.push_back(row[i]);
    }

    Elements meta;
    if (state.fightSlot >= 0) {
        Card& c = state.room.room[state.fightSlot];
        meta.push_back(text("FIGHT " + ShortLabel(c) + ":") | bold | color(Color::Yellow));
        meta.push_back(text("   ") | color(Color::GrayDark));
        meta.push_back(text("[W] Weapon  [B] Barehanded  [Q] Cancel") | color(Color::Yellow) | bold);
    } else if (state.hasRunThisTurn) {
        meta.push_back(text("[R] Retreat (used)") | dim | color(Color::GrayDark));
    } else {
        meta.push_back(text("[R] Retreat / Skip room") | dim | color(Color::Cyan));
        meta.push_back(text("   ") | color(Color::GrayDark));
        meta.push_back(text("[Q] Quit") | dim | color(Color::GrayDark));
    }

    return vbox({
        hbox(rowJoined) | center,
        hbox(meta) | center,
    });
}

// ── Game Over ────────────────────────────────────────────────

Element BuildGameOver(GameState& state) {
    Elements e;
    if (state.won) {
        // Gold trophy
        std::vector<std::string> trophy = {
            " ___________",
            " '._==_==_=_.'",
            " .-\\:      /-.",
            "| (|:.     |) |",
            " '-|:.     |-'",
            "   \\::.    /",
            "    '::. .'",
            "      ) (",
            "    _.' '._",
            "   `\"\"\"\"\"\"\"`",
        };
        for (auto& line : trophy)
            e.push_back(text(line) | color(Color::Yellow) | bold | center);
        e.push_back(text(""));
        e.push_back(text("YOU SURVIVED THE DUNGEON") | color(Color::Green) | bold | center);
        e.push_back(text(""));
        e.push_back(text("Score: " + std::to_string(state.player.health) + " HP remaining")
            | color(Color::Green) | center);
    } else {
        std::vector<std::string> grave = {
            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⠀⠀⣠⣔⡿⠛⠒⠒⡕⢄⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⣀⣴⣳⠃⠀⠀⠀⠀⠘⢎⡦⣄⠀⠀⠀⠀",
            "⠀⠀⠀⣜⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠢⣳⠀⠀⠀",
            "⠀⠀⢸⣸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⡆⠀⠀",
            "⠀⠀⠘⡏⢀⢴⠶⣤⢄⢲⣲⠦⣦⣤⡤⡀⡇⠇⠀⠀",
            "⠀⠀⠀⣧⠀⣾⢀⣸⡸⠘⢸⠀⣿⠀⣸⡏⣧⠀⠀⠀",
            "⠀⠀⠀⢹⠀⣿⠿⡯⡀⢀⣼⢀⣿⠛⠉⠀⢻⠀⠀⠀",
            "⠀⠀⠀⣿⠐⠛⠂⠘⠛⠒⠛⠊⠛⠂⠀⢸⢸⠀⠀⠀",
            "⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡼⠀⠀⠀",
            "⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡆⠀⠀⠀",
            "⠀⠀⢀⢾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡷⡀⠀⠀",
            "⠀⣠⠃⠘⠊⠉⠛⠛⠋⠩⠩⠭⠍⠛⠛⠛⠃⠐⡄⠀",
            "⠀⣯⡉⠉⢉⡉⠉⠉⠉⠉⠉⠉⣉⣉⣉⣉⣉⣉⣹⠀",
            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
            "⡴⡤⡤⣤⡤⡤⣤⣤⢠⣤⣤⠀⢰⡄⣤⣶⡴⢶⣶⡴",
        };
        for (auto& line : grave)
            e.push_back(text(line) | color(Color::Red) | center);
        e.push_back(text(""));
        e.push_back(text("YOU HAVE PERISHED") | color(Color::Red) | bold | center);
        e.push_back(text(""));
        e.push_back(text("Score: " + std::to_string(state.player.health) + " HP left")
            | color(Color::Red) | center);
    }
    e.push_back(text(""));
    e.push_back(text("[Q] Quit") | dim | color(Color::GrayDark) | center);
    return vbox(e) | center | flex;
}

// ── Main Layout ──────────────────────────────────────────────

Element BuildUI(GameState& state) {
    if (state.gameOver)
        return vbox({text("") | flex, BuildGameOver(state), text("") | flex});

    Element content = vbox({
        text("SCOUNDREL") | bold | color(Color::Cyan) | center,
        text(""),
        text("DUNGEON ROOM") | bold | color(Color::GrayDark) | center,
        text(""),
        hbox({
            RenderCard(state.room.room[0]),
            text("   "),
            RenderCard(state.room.room[1]),
            text("   "),
            RenderCard(state.room.room[2]),
            text("   "),
            RenderCard(state.room.room[3]),
        }) | center,
        text(""),
        hbox({
            BuildPlayerPanel(state),
            text("  ") | color(Color::GrayDark),
            BuildStatusPanel(state),
        }) | center,
        text(""),
        BuildActionBar(state),
    }) | border | color(Color::GrayDark);

    return vbox({
        text("") | flex,
        hbox({
            text("") | flex,
            content,
            text("") | flex,
        }),
        text("") | flex,
    });
}

// ── Main ─────────────────────────────────────────────────────

int main(void) {
    GameState state;

    auto screen = ScreenInteractive::Fullscreen();

    screen.Loop(CatchEvent(
        Renderer([&]() -> Element {
            if (state.player.isDead && !state.gameOver) {
                state.gameOver = true;
                state.won = false;
            }
            if (state.room.cardsLeft <= 1 && !state.room.isComplete && !state.gameOver) {
                state.room.isComplete = true;
                state.player.ResetPotionsPerRoom();
                state.hasRunThisTurn = false;
            }
            if (state.room.isComplete && state.deck.Size() == 0 && !state.gameOver) {
                state.gameOver = true;
                state.won = true;
            }
            if (state.room.isComplete && state.deck.Size() > 0 && !state.gameOver) {
                state.room.LoadNext();
                state.room.isComplete = false;
                state.discardCount = 0;
                state.hasRunThisTurn = false;
            }
            return BuildUI(state);
        }),
        [&](Event event) -> bool {
            if (state.gameOver) {
                if (event == Event::Character('q') || event == Event::Character('Q')) {
                    screen.Exit();
                    return true;
                }
                return false;
            }

            auto act = [&](int idx, bool bareFight = false) {
                Card& card = state.room.room[idx];
                if (card.type == NONE)
                    return;

                state.player.Pick(card, bareFight);
                state.room.cardsLeft--;
                state.discardCount++;
                state.hasRunThisTurn = false;

                if (state.player.isDead) {
                    state.gameOver = true;
                } else if (state.room.cardsLeft <= 1) {
                    state.room.isComplete = true;
                    state.player.ResetPotionsPerRoom();
                }
            };

            auto choose = [&](int idx) {
                Card& card = state.room.room[idx];
                if (card.type == NONE)
                    return;
                bool isMonster = card.type == SPADES || card.type == CLUBS;
                if (isMonster && state.player.weapon.type != NONE)
                    state.fightSlot = idx;
                else
                    act(idx);
            };

            if (state.fightSlot >= 0) {
                if (event == Event::Character('w') || event == Event::Character('W')) {
                    act(state.fightSlot, false);
                    state.fightSlot = -1;
                    return true;
                }
                if (event == Event::Character('b') || event == Event::Character('B')) {
                    act(state.fightSlot, true);
                    state.fightSlot = -1;
                    return true;
                }
                if (event == Event::Character('q') || event == Event::Character('Q')) {
                    state.fightSlot = -1;
                    return true;
                }
                return false;
            }

            if (event == Event::Character('q') || event == Event::Character('Q')) {
                screen.Exit();
                return true;
            }

            if (event == Event::Character('1')) { choose(0); return true; }
            if (event == Event::Character('2')) { choose(1); return true; }
            if (event == Event::Character('3')) { choose(2); return true; }
            if (event == Event::Character('4')) { choose(3); return true; }

            if (event == Event::Character('r') || event == Event::Character('R')) {
                if (!state.hasRunThisTurn && !state.gameOver) {
                    state.room.Run();
                    state.hasRunThisTurn = true;
                    state.player.ResetPotionsPerRoom();
                    state.discardCount = 0;
                }
                return true;
            }

            return false;
        }
    ));

    return 0;
}