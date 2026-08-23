#pragma once

#include <cstddef>
#include <deque>
#include "card.hpp"

struct Deck 
{
        std::deque<Card> deck;

        void PushDeck(const Card &card);
        Card PopDeck();
        void ShuffleDeck();
        size_t Size();
        Deck();
};

