#include <deque>
#include "card.hpp"

struct Deck 
{
        std::deque<Card> deck;

        void PushDeck(Card card);
        Card PopDeck();
        void ShuffleDeck(std::deque<Card> deck);
        Deck();
};

