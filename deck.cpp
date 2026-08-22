#include "deck.hpp"
#include "card.hpp"
#include <deque>
#include <vector>
#include <ctime>

void Deck::PushDeck(Card card)
{
    this->deck.push_back(card);
}

Card Deck::PopDeck()
{
    Card card = this->deck.front();
    this->deck.pop_front();
    return card;
}



void Deck::ShuffleDeck(std::deque<Card> deck)
{
    std::vector<Card> cards;

    // selectively push cards in it?

    for (int i = 2; i < 15; i++) {
        cards.push_back((Card){ .type = SPADES, .value = i});
        cards.push_back((Card){ .type = CLUBS, .value = i});
    }

    for (int i = 2; i < 11; i++) {
        cards.push_back((Card){ .type = DIAMONDS, .value = i});
        cards.push_back((Card){ .type = HEARTS, .value = i});
    }

    srand(time(0));

    for (int i = 0; i < cards.size(); i++) {
        int r = i + (rand() % (44 - i));
        std::swap(cards[i], cards[r]);
    }

    for (int i = 0; i < cards.size(); i++) {
        Deck::PushDeck(cards[i]);
    }

}


Deck::Deck()
{
    ShuffleDeck(deck);
}

