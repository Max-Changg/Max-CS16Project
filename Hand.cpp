#include "Hand.h"
// #include "Card.h"


Hand::Hand() {
  counter = 0;
  capacity = 2;
  hand = new Card[capacity];
}

Hand::Hand(const Hand& other) {
  counter = other.counter;
  capacity = other.capacity;
  hand = new Card[capacity];
  for (size_t i = 0; i < counter; ++i) {
    hand[i] = other.hand[i];
  }
}

Hand::~Hand() {
  delete [] hand;
}

void Hand::sort_cards() {
  Card* new_hand = new Card[capacity];
  Card newly_added = hand[counter - 1];
  bool inserted = false;
  for (size_t i = 0; i < counter; ++i) {
    size_t j = i;
    if ((newly_added > hand[i]) && (inserted == false)) {
      inserted = true;
      new_hand[i] = newly_added;
    }
    if (inserted == true) {
      ++j;
    }
    if (j < counter) {
      new_hand[j] = hand[i];
    }
  }
  delete [] hand;
  hand = new_hand;
}

void Hand::add(const Card card_hand) {
  if(counter == capacity) {
      Card* temp = new Card[2*counter];
      for(size_t i = 0; i < counter; ++i) {
        temp[i] = hand[i];
      }

      capacity *= 2;
      delete [] hand;
      hand = temp;
    }

  hand[counter] = card_hand;
  counter += 1;
  this->sort_cards();
}


void Hand::clear() {
  if (counter != 0) {
    delete [] hand;
    hand = new Card[2];
    counter = 0;
    capacity = 2;
  }
}

size_t Hand::count() const {
  return this->counter;
}

Card Hand::get(size_t index) const {
  return hand[index];
}

void Hand::print() const {
    for(size_t i = 0; i < counter; ++i) {
      hand[i].print();
      if (i != counter -1) {
        std::cout << ' ';
      }
    }
}

Hand* make_hand() {
  return new Hand();
}

// int main() {
//   Card card1 = Card(2, CLUBS);
//   Card card2 = Card(9, DIAMONDS);
//   Card card3 = Card(7, SPADES);
//   Card card4 = Card(13, HEARTS);

//   Hand hand1 = Hand();
//   hand1.add(card1);
//   hand1.add(card2);
//   hand1.add(card3);
//   hand1.add(card4);
//   Hand hand2 = Hand(hand1);
//   hand1.print();
//   hand2.print();
// }