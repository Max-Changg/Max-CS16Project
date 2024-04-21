#include "Hand.h"
// #include "Card.h"
// #include "Hand.cpp"
#include <iostream>


bool hasNoCards(const Hand &hand) {
    if (hand.count() == 0) {
        return true;
    }
    else {
        return false;
    }
}

Hand* hasHighCard(const Hand &hand) {
    Card highest = hand.get(0);
    for (size_t i = 0; i < hand.count(); ++i) {
        if (hand.get(i) > highest) {
            highest = hand.get(i);
        }
    }
    Hand* result = new Hand();
    result->add(highest);
    // std::cout << "highcard is ";
    return result;
}

Hand* hasPair(const Hand &hand, unsigned int num) {
    Hand* pair = new Hand();
    Hand sorted = hand;
    sorted.sort_cards();
    for (size_t i = 0; i < hand.count(); ++i) {
        for (size_t j = i + 1; j < hand.count(); ++j) {
            if (sorted.get(i).rank == sorted.get(j).rank){
                pair->add(sorted.get(i));  // Found a pair
                pair->add(sorted.get(j));
                if (num == 2) {
                    // std::cout << "one pair is ";
                    return pair;
                }
            }
        }
        if (pair->count() == 4) { // got 2 pairs
            // std::cout << "2 pair is ";
            return pair;
        }
    }
    return pair; // got no pair
}

Hand* hasNumKind(const Hand &hand, unsigned int num) {
    Hand sorted = hand;
    sorted.sort_cards();
    Hand* sameRank = new Hand();
    bool firstMatch = false;
    for (size_t i = 0; i < hand.count(); ++i) {
        for (size_t j = i + 1; j < hand.count(); ++j) {
            if (sorted.get(i).rank == sorted.get(j).rank) {
                if (firstMatch == false) {
                    sameRank->add(sorted.get(i));
                    firstMatch = true;
                }
                sameRank->add(hand.get(j));
                
            }
        }
        if (sameRank->count() == num) {
            return sameRank;
        }
        else {
            sameRank->clear();
            firstMatch = false;
        }
    }
    return sameRank;
}

Hand* hasStraight(const Hand &hand) {
    Hand sorted = hand;
    sorted.sort_cards();
    Hand* straight = new Hand();
    if (hand.count() < 5) {
        return straight;
    }
    bool started = false;
    for (size_t i = 0; i < sorted.count(); ++i) {
        Card highest = sorted.get(i);
        for (size_t j = i + 1; j < sorted.count(); ++j) {
            if (highest.rank == sorted.get(j).rank + 1) {
                if (started == false) {
                    straight->add(sorted.get(i));
                    started = true;
                }
                straight->add(sorted.get(j));
                highest = sorted.get(j);
            }
            if (straight->count() == 5) { // found straight
            // std::cout << "straight is";
            return straight;
            }
            else if ((straight->count() == 4) && (sorted.get(0).rank == ACE) && 
            ((straight->get(3)).rank == 2)) {
                straight->add(sorted.get(0));
                return straight;
            }
        }
        straight->clear();
        started = false;
    }
    // no straight
    return straight;
}

Hand* hasFlush(const Hand &hand) {
    Hand sorted = hand;
    sorted.sort_cards();
    if (hand.count() < 5) {
        return make_hand();
    }
    // sort by suit
    Hand* spades = new Hand();
    Hand* diamonds = new Hand();
    Hand* hearts = new Hand();
    Hand* clubs = new Hand();
    for (size_t i = 0; i < hand.count(); ++i){
        if ((hand.get(i).suit == SPADES) && (spades->count() != 5)) {
            spades->add(hand.get(i));
        }
        else if ((hand.get(i).suit == DIAMONDS) && (diamonds->count() != 5)) {
            diamonds->add(hand.get(i));
        }
        else if ((hand.get(i).suit == HEARTS) && (hearts->count() != 5)) {
            hearts->add(hand.get(i));
        }
        else if ((hand.get(i).suit == CLUBS) && (clubs->count() != 5)) { 
            clubs->add(hand.get(i));
        }
    }
    if ((spades->count() == 5) && (hearts->count() == 5)) {
        for (size_t i = 0; i < 5; ++i) {
            if (spades->get(i).rank > hearts->get(i).rank) {
                delete diamonds;
                delete hearts;
                delete clubs;
                return spades;
            }
            else if (spades->get(i).rank < hearts->get(i).rank) {
                delete spades;
                delete diamonds;
                delete clubs;
                return hearts;
            }
        }
        delete diamonds;
        delete hearts;
        delete clubs;
        return spades;
    }
    if (spades->count() == 5) {
        delete diamonds;
        delete hearts;
        delete clubs;
        return spades;
    }
    else if (diamonds->count() == 5) {
        delete spades;
        delete hearts;
        delete clubs;
        return diamonds;
    }
    else if (hearts->count() == 5) {
        delete diamonds;
        delete spades;
        delete clubs;
        return hearts;
    }
    else if (clubs->count() == 5) {
        delete diamonds;
        delete hearts;
        delete spades;
        return clubs;
    }
    else {
        delete spades;
        delete diamonds;
        delete hearts;
        delete clubs;
        return make_hand();
    }
}

Hand* hasFullHouse(const Hand &hand) {
    Hand* fullHouse = new Hand();
    Hand sorted = hand;
    sorted.sort_cards();
    Hand* triple = hasNumKind(hand, 3);
    if (triple->count() == 3) {
        for (size_t i = 0; i < 3; ++i) {
            fullHouse->add(triple->get(i));
        }
        delete triple;
        for (size_t j = 0; j < hand.count(); ++j) {
            for (size_t k = j+1; k < hand.count(); ++k) {
                if ((sorted.get(j).rank == sorted.get(k).rank) && (sorted.get(j).rank != fullHouse->get(0).rank)) {
                    fullHouse->add(sorted.get(j));
                    fullHouse->add(sorted.get(k));
                    // std::cout << "full house is ";
                    return fullHouse; // count = 5
                }
            }
        }
        return fullHouse; // count = 3
    }
    else {
        delete triple;
        return fullHouse; // count = 0
    }   
}

Hand* hasStraightFlush(const Hand &hand) {
    Hand sorted = hand;
    sorted.sort_cards();
    Hand* straightFlush = new Hand();
    if (hand.count() < 5) {
        return straightFlush;
    }
    bool started = false;
    for (size_t i = 0; i < sorted.count(); ++i) {
        Card highest = sorted.get(i);
        for (size_t j = i + 1; j < sorted.count(); ++j) {
            if ((highest.rank == sorted.get(j).rank + 1) && (highest.suit == sorted.get(j).suit)) {
                if (started == false) {
                    straightFlush->add(sorted.get(i));
                    started = true;
                }
                straightFlush->add(sorted.get(j));
                highest = sorted.get(j);
            }
            if (straightFlush->count() == 5) { // got straight flush
                // std::cout << "straight flush is ";
                return straightFlush;
            }
            else if ((straightFlush->count() == 4)
            && (sorted.get(j).rank == 2) && (sorted.get(j).suit == highest.suit)) {
                for (size_t k = 0; k < 4; ++k) {
                    if ((sorted.get(k).rank == ACE) 
                    && (sorted.get(k).suit == highest.suit)) {
                        straightFlush->add(sorted.get(k));
                        return straightFlush;
                    }
                }
                
            }
        }
        straightFlush->clear();
    }
    return straightFlush;
}

Hand* best_hand(const Hand& cards) {
    if (hasNoCards(cards) == true) { // no cards lol
        return make_hand();
    }
    Hand* straightFlush = hasStraightFlush(cards);
    Hand* fourKind = hasNumKind(cards, 4);
    Hand* fullHouse = hasFullHouse(cards);
    Hand* flush = hasFlush(cards);
    Hand* straight = hasStraight(cards);
    Hand* threeKind = hasNumKind(cards, 3);
    Hand* twoPair = hasPair(cards, 4);
    Hand* onePair = hasPair(cards, 2);
    Hand* highCard = hasHighCard(cards);


    if (straightFlush->count() == 5) { // straight flush
        delete fourKind;
        delete fullHouse;
        delete flush;
        delete straight;
        delete threeKind;
        delete twoPair;
        delete onePair;
        delete highCard;
        // std::cout << "straightflush";
        return straightFlush;
    }
    else if (fourKind->count() == 4) { // 4 of a kind
        delete straightFlush;
        delete fullHouse;
        delete flush;
        delete straight;
        delete threeKind;
        delete twoPair;
        delete onePair;
        delete highCard;
        // std::cout << "fourkind";
        return fourKind;
    }
    else if (fullHouse->count() == 5) { // full house
        delete straightFlush;
        delete fourKind;
        delete flush;
        delete straight;
        delete threeKind;
        delete twoPair;
        delete onePair;
        delete highCard;
        // std::cout << "fullhouse";
        return fullHouse;
    }
    else if (flush->count() == 5) { // flush
        delete straightFlush;
        delete fourKind;
        delete fullHouse;
        delete straight;
        delete threeKind;
        delete twoPair;
        delete onePair;
        delete highCard;
        // std::cout << "flush";
        return flush;
    }
    else if (straight->count() == 5) { // straight
        delete straightFlush;
        delete fourKind;
        delete fullHouse;
        delete flush;
        delete threeKind;
        delete twoPair;
        delete onePair;
        delete highCard;
        // std::cout << "straight";
        return straight;
    }
    else if (threeKind->count() == 3) { // 3 of a kind
        delete straightFlush;
        delete fourKind;
        delete fullHouse;
        delete flush;
        delete straight;
        delete twoPair;
        delete onePair;
        delete highCard;
        // std::cout << "threekind";
        return threeKind;
    }
    else if (twoPair->count() == 4) { // two pair
        delete straightFlush;
        delete fourKind;
        delete fullHouse;
        delete flush;
        delete straight;
        delete threeKind;
        delete onePair;
        delete highCard;
        // std::cout << "twopair";
        return twoPair;
    }
    else if (onePair->count() == 2) { // one pair
        delete straightFlush;
        delete fourKind;
        delete fullHouse;
        delete flush;
        delete straight;
        delete threeKind;
        delete twoPair;
        delete highCard;
        // std::cout << "onepair";
        return onePair;
    }
    else { // high card
        delete straightFlush;
        delete fourKind;
        delete fullHouse;
        delete flush;
        delete straight;
        delete threeKind;
        delete twoPair;
        delete onePair;
        // std::cout << "highcard";
        return highCard;
    }
    // std::cout << "whaaaaa";
    return make_hand();
}


// int main() {
//     Card card1 = Card(KING, SPADES);
//     Card card2 = Card(KING, HEARTS);
//     Card card3 = Card(10, SPADES);
//     Card card4 = Card(10, HEARTS);
//     Card card5 = Card(7, SPADES);
//     Card card6 = Card(7, HEARTS);
//     Card card7 = Card(6, SPADES);
//     Card card8 = Card(4, HEARTS);
//     Card card9 = Card(3, SPADES);
//     Card card10 = Card(3, HEARTS);
//     Card card11 = Card(2, CLUBS);

//     Hand hand1 = Hand();
//     hand1.add(card1);
//     hand1.add(card2);
//     hand1.add(card3);
//     hand1.add(card4);
//     hand1.add(card5);
//     hand1.add(card6);
//     hand1.add(card7);
//     hand1.add(card8);
//     hand1.add(card9);
//     hand1.add(card10);
//     // hand1.add(card11);

//     // hand1.add(card5);
//     // hand1.add(card1);
//     // hand1.add(card1);
//     // hand1.add(card5);
//     // Hand hand2 = Hand();
//     hand1.print();
//     std::cout << '\n';
//     // hand2.print();
//     (best_hand(hand1))->print();
// }


// bool started = false;
//     for (size_t i = 0; i < sorted.count(); ++i) {
//         Card sameSuit = sorted.get(i);
//         for (size_t j = i + 1; j < sorted.count(); ++j) {
//             if (sameSuit.suit == sorted.get(j).suit) {
//                 if (started == false) {
//                     flush->add(sorted.get(i));
//                     started = true;
//                 }
//                 flush->add(sorted.get(j));
//             }
//             if (flush->count() == 5) { // got flush
//                 // std::cout << "flush is ";
//                 return flush;
//             }
//         }
//         flush->clear();
//         started = false;
//     } // no flush
//     return flush;