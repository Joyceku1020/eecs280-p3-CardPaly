// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"
#include "Card.h"
#include <sstream>

using namespace std;


Pack::Pack() {
    int index = 0;
    for (int i = 0; i < NUM_SUITS; i++) {
        for (int j = 7; j < NUM_RANKS; j++) {
            Card c(RANK_NAMES_BY_WEIGHT[j], 
                SUIT_NAMES_BY_WEIGHT[i]);
            cards.at(index) = c;
            index++;
        }
    }
    next = 0;
}

Pack::Pack(std::istream& pack_input) {
    string of = "";
    string rank = "";
    string suit = "";
    int index = 0;
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> rank >> of >> suit;
        Card c(rank, suit);
        cards.at(index) = c;
        index++;
    }
    next = 0;
}

Card Pack::deal_one() {
    int currNext = next;
    next++;
    return cards.at(currNext);
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    const int middle = PACK_SIZE/2;
    Card tempFirst[middle];
    Card tempSecond[middle];
    for (int a = 0; a < 7; a++) {
        for (int i = 0; i < middle; i++) {
            tempFirst[i] = cards[i];
        }
        int index = 0;
        for (int j = middle; j < PACK_SIZE; j++) {
            tempSecond[index] = cards[j];
            index++;
        }

        int even = 0;
        for (int l = 0; l < PACK_SIZE; l += 2) {
            cards[l] = tempSecond[even];
            even++;
        }

        int odd = 0;
        for (int k = 1; k < PACK_SIZE; k += 2) {
            cards[k] = tempFirst[odd];
            odd++;
        }
    }
    reset();
    
} 

bool Pack::empty() const {
    return (next == PACK_SIZE);
}