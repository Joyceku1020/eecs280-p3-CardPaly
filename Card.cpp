// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"

using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these

constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

Card::Card() {
    suit = SUIT_SPADES;
    rank = RANK_TWO;
}

Card::Card(const std::string &rank_in, const std::string &suit_in) {
    suit = suit_in;
    rank = rank_in;
}

std::string Card::get_rank() const {
    return rank;
}

 std::string Card::get_suit() const {
    return suit;
 }

 std::string Card::get_suit(const std::string &trump) const {
    if(is_left_bower(trump)) return trump;
    return suit;
 }

bool Card::is_face_or_ace() const {
    if(rank == RANK_JACK || rank == RANK_QUEEN || 
        rank == RANK_KING || rank == RANK_ACE) return true;
    return false;
}

bool Card::is_right_bower(const std::string &trump) const {
    if(rank == RANK_JACK && suit == trump) return true;
    return false;
}

bool Card::is_left_bower(const std::string &trump) const {
    if (rank == RANK_JACK) {
        if (trump == SUIT_HEARTS) {
            return (suit == SUIT_DIAMONDS);
        }
        else if (trump == SUIT_DIAMONDS) {
            return (suit == SUIT_HEARTS);
        }
        else if (trump == SUIT_CLUBS) {
            return (suit == SUIT_SPADES);
        }
        else if (trump == SUIT_SPADES) {
            return (suit == SUIT_CLUBS);
        }
    }
    return false;
}

bool Card::is_trump(const std::string &trump) const {
    return (suit == trump || is_left_bower(trump));
}

bool operator<(const Card &lhs, const Card &rhs) {
    int lhsRank = 0;
    int rhsRank = 0;
    int lhsSuit = 0;
    int rhsSuit = 0;

    for (int i = 0; i < NUM_RANKS; i++) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            lhsRank = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            rhsRank = i;
        }
    }
    if (lhsRank < rhsRank) {
        return true;
    }
    else if (lhsRank > rhsRank) {
        return false;
    }
    else {
        for (int j = 0; j < NUM_SUITS; j++) {
            if (SUIT_NAMES_BY_WEIGHT[j] == lhs.get_suit()) {
                lhsSuit = j;
            }
            if (SUIT_NAMES_BY_WEIGHT[j] == rhs.get_suit()) {
                rhsSuit = j;
            }
        }
        if (lhsSuit < rhsSuit) {
            return true;
        }
        return false;
    }
}

bool operator<=(const Card &lhs, const Card &rhs) {
    return !(operator>(lhs, rhs));
}

bool operator>(const Card &lhs, const Card &rhs) {
    int lhsRank = 0;
    int rhsRank = 0;
    int lhsSuit = 0;
    int rhsSuit = 0;

    for (int i = 0; i < NUM_RANKS; i++) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            lhsRank = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            rhsRank = i;
        }
    }
    if (lhsRank > rhsRank) {
        return true;
    }
    else if (lhsRank <rhsRank) {
        return false;
    }
    else {
        for (int j = 0; j < NUM_SUITS; j++) {
            if (SUIT_NAMES_BY_WEIGHT[j] == lhs.get_suit()) {
                lhsSuit = j;
            }
            if (SUIT_NAMES_BY_WEIGHT[j] == rhs.get_suit()) {
                rhsSuit = j;
            }
        }
        if (lhsSuit > rhsSuit) {
            return true;
        }
        return false;
    }
}

bool operator>=(const Card &lhs, const Card &rhs) {
    return !(operator<(lhs, rhs));
}

bool operator==(const Card &lhs, const Card &rhs) {
    int lhsRank = 0;
    int rhsRank = 0;
    int lhsSuit = 0;
    int rhsSuit = 0;

    for (int i = 0; i < NUM_RANKS; i++) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            lhsRank = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            rhsRank = i;
        }
    }
    for (int j = 0; j < NUM_SUITS; j++) {
        if (SUIT_NAMES_BY_WEIGHT[j] == lhs.get_suit()) {
            lhsSuit = j;
        }
        if (SUIT_NAMES_BY_WEIGHT[j] == rhs.get_suit()) {
            rhsSuit = j;
        }
    }
    return (lhsRank == rhsRank && lhsSuit == rhsSuit);
}

bool operator!=(const Card &lhs, const Card &rhs) {
    return !(operator==(lhs, rhs));
}

std::string Suit_next(const std::string &suit) {
    int index= 0;
    for(int i = 0; i < NUM_SUITS; i++) {
        if(suit == SUIT_NAMES_BY_WEIGHT[i]) {
            index = i;
            break;
        }
    }
    if(index < 2) return SUIT_NAMES_BY_WEIGHT[index + 2];
    return SUIT_NAMES_BY_WEIGHT[index - 2];
}

std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    if(a.is_right_bower(trump)) return false;
    if(b.is_right_bower(trump)) return true;
    if(a.is_left_bower(trump)) return false;
    if(b.is_left_bower(trump)) return true;
    if(a.is_trump(trump) && b.is_trump(trump)) {
        if(operator<(a, b)) return true;
        return false;
    }
    if(a.is_trump(trump)) return false;
    if(b.is_trump(trump)) return true;
    if(operator<(a, b)) return true;
    return false;
}

bool Card_less(const Card &a, const Card &b, 
    const Card &led_card, const std::string &trump) {
    if(a.is_right_bower(trump)) return false;
    if(b.is_right_bower(trump)) return true;
    if(a.is_left_bower(trump)) return false;
    if(b.is_left_bower(trump)) return true;
    if(a.is_trump(trump) && b.is_trump(trump)) {
        if(operator<(a, b)) return true;
        return false;
    }
    if(a.is_trump(trump) && a.get_rank() != Card::RANK_TWO) return false;
    if(b.is_trump(trump) && b.get_rank() != Card::RANK_TWO) return true;
    if(a.get_suit() == led_card.get_suit() && b.get_suit() == led_card.get_suit()) {
        if(operator<(a,b)) return true;
        return false;
    }
    if(a.get_suit() == led_card.get_suit(trump)) return false;
    if(b.get_suit() == led_card.get_suit(trump)) return true;
    if(operator<(a,b)) return true;
    return false;
}



// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
