#include "../include/deck.hpp"
#include "../include/card.hpp"
#include <cstddef>
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

size_t Deck::Size()
{
    return this->deck.size();
}

void Deck::ShuffleDeck()
{
    std::vector<Card> cards;

    // selectively push cards in it?

    for (size_t i = 2; i < 15; i++) {
        cards.push_back(Card{ SPADES, i});
        cards.push_back(Card{ CLUBS, i});
    }

    for (size_t i = 2; i < 11; i++) {
        cards.push_back(Card{ DIAMONDS,  i});
        cards.push_back(Card{ HEARTS, i});
    }

    srand(time(0));

    for (size_t i = 0; i < cards.size(); i++) {
        int r = i + (rand() % (cards.size() - i));
        std::swap(cards[i], cards[r]);
    }


    for (size_t i = 0; i < cards.size(); i++) {
        Deck::PushDeck(cards[i]);
    }

}

Deck::Deck()
{
    ShuffleDeck();
}

