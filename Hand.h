#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <string>


class Hand {
    Card* hand;
    size_t counter;
    size_t capacity;

public:
    void sort_cards();
    Hand();
// Hand() is a default constructor. It should take no arguments and 
// initialize the hand as an empty hand.
    Hand(const Hand& other);
// Hand(const Hand& other) is a copy constructor. It should initialize 
// the hand as a copy of other.
    ~Hand();
// ~Hand() is a destructor. It should free all heap memory owned by the hand.
    void add(Card card);
// void add(Card card) should add card to the hand.
    void clear();
// void clear() should remove all cards from the hand.
    size_t count() const;
// size_t count() const should return the number of cards in the hand.
    Card get(size_t index) const;
// Card get(size_t index) const should return the card at index index. 
// This function will only be tested with valid indices.
    void print() const;
// void print() const should print the cards in the hand in order,
// separated by one space character. It should print nothing after
// the final card (no space and no newline).


};

Hand* make_hand();
Hand* best_hand(const Hand& cards);

#endif