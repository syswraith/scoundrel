#include <deque>
#include "card.hpp"

class Deck 
{
    public:
        std::deque<Card> deck;

        void PushDeck(Card card);
        Card PopDeck();
        void ShuffleDeck(std::deque<Card> deck);
        Deck();
};

