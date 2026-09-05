#pragma once

#include <cstddef>

enum CardType {
    NONE,
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

struct Card {
    CardType type;
    size_t value;
};