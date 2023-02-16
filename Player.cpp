// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Player.h"
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class SimplePlayer : public Player {
  private:
    std::string name = "";
    std::vector<Card> hands;
  public:
    SimplePlayer(const std::string playerName) {
        name = playerName;
    }
    const std::string & get_name() const {
        return name;
    }
    
    void add_card(const Card &c) {
        assert(hands.size() < MAX_HAND_SIZE);
        hands.push_back(c);
    }
    
    bool make_trump(const Card &upcard, bool is_dealer, 
        int round, std::string &order_up_suit) const {
        assert(round == 1 || round == 2);
        int numTrump = 0;
        string trumpSuit = "";

        if (round == 1) {
            trumpSuit = upcard.get_suit();
            for (int i = 0; i < hands.size(); i++) {
                if ((hands.at(i).get_suit() == trumpSuit && hands.at(i).is_face_or_ace()) 
                  || hands.at(i).is_left_bower(trumpSuit)) {
                    numTrump++;
                }
            }
            if (numTrump >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            return false;
        }
        else {
            trumpSuit = Suit_next(upcard.get_suit());
            if (is_dealer) {
                order_up_suit = trumpSuit;
                return true;
            }
            for (int j = 0; j < hands.size(); j++) {
                if (hands.at(j).get_suit() == trumpSuit) {
                    numTrump++;
                }
            }
            if (numTrump >= 1) {
                order_up_suit = trumpSuit;
                return true;
            }
            return false;
        }
    }
    
    void add_and_discard(const Card &upcard) {
        assert(hands.size() >= 1);
        hands.push_back(upcard);
        Card lowestCard = hands.at(0);
        int lowestIndex = 0;
        for (int i = 0; i < hands.size(); i++) {
            if (Card_less(hands.at(i), lowestCard, upcard.get_suit())) {
                lowestCard = hands.at(i);
                lowestIndex = i;
            }
        }
        hands.erase(hands.begin() + lowestIndex);
    }
    
    Card lead_card(const std::string &trump) {
        assert(hands.size() >= 1);
        int numTrumpCards = 0;
        int highestCardIndex = 0;
        Card highestCard(Card::RANK_TWO, Card::SUIT_CLUBS);
        for (int i = 0; i < hands.size(); i++) {
            if (hands.at(i).is_trump(trump)) {
                numTrumpCards++;
            }
        }
        if (numTrumpCards == hands.size()) {
            for (int i = 0; i < hands.size(); i++) {
                if (!Card_less(hands.at(i), highestCard, trump)) { //changed here
                    highestCard = hands.at(i);
                    highestCardIndex = i;
                }
            }
        }
        else {
            for (int i = 0; i < hands.size(); i++) {
                if (!Card_less(hands.at(i), highestCard, trump)  //changed here
                  && !hands.at(i).is_trump(trump)) {
                    highestCard = hands.at(i);
                    highestCardIndex = i;
                }
            }
        }
        hands.erase(hands.begin() + highestCardIndex);
        return highestCard;
    }
    
    Card play_card(const Card &led_card, const std::string &trump) {
        assert(hands.size() >= 1);
        string ledSuit;
        ledSuit = led_card.get_suit(trump);
        int numLedSuit = 0;
        Card highestLedSuit;
        Card lowestCard;
        int returningCardIndex = 0;
        for (int i = 0; i < hands.size(); i++) {
            if (hands.at(i).get_suit(trump) == ledSuit) {
                numLedSuit++;
            }
        }
        if (numLedSuit >= 1) {
            for (int j = 0; j < hands.size(); j++) {
                if (hands.at(j).get_suit(trump) == ledSuit) {
                    if (Card_less(highestLedSuit, hands.at(j), led_card, trump)) {
                        highestLedSuit = hands.at(j);
                        returningCardIndex = j;
                    }
                }
            }
            hands.erase(hands.begin() + returningCardIndex);
            return highestLedSuit;
        }
        else {
            lowestCard = hands.at(0);
            for (int k = 0; k < hands.size(); k++) {
                if (Card_less(hands.at(k), lowestCard, led_card, trump)) {
                    lowestCard = hands.at(k);
                    returningCardIndex = k;
                }
            }
            hands.erase(hands.begin() + returningCardIndex);
            return lowestCard;
        }
    }
};

class HumanPlayer : public Player {
  private:
    std::string name = "";
    std::vector<Card> hands;
  public:
    HumanPlayer(const std::string playerName) {
        name = playerName;
        std::sort(hands.begin(), hands.end());
    }
    const std::string & get_name() const {
        return name;
    }
    
    void add_card(const Card &c) {
        std::sort(hands.begin(), hands.end());
        assert(hands.size() < MAX_HAND_SIZE);
        hands.push_back(c);
        std::sort(hands.begin(), hands.end());
    }
    
    bool make_trump(const Card &upcard, bool is_dealer, 
        int round, std::string &order_up_suit) const {
        print_hand();
        cout << "Human player " << name << 
            ", please enter a suit, or \"pass\":\n";
        string suit = "";
        cin >> suit;
        if (suit == "pass") {
            return false;
        }
        else {
            order_up_suit = suit;
            return true;
        }
    }
    
    void add_and_discard(const Card &upcard) {
        std::sort(hands.begin(), hands.end());
        assert(hands.size() >= 1);
        print_hand();
        hands.push_back(upcard);
        int discardIndex = 0;
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << 
            ", please select a card to discard:\n";
        cin >> discardIndex;
        if (discardIndex == -1) {
            hands.erase(hands.begin() + (hands.size() - 1));
        }
        else {
            hands.erase(hands.begin() + discardIndex);
        }
        std::sort(hands.begin(), hands.end());
    }
    
    Card lead_card(const std::string &trump) {
        std::sort(hands.begin(), hands.end());
        print_hand();
        int leadCardIndex = 0;
        cout << "Human player " << name << ", please select a card:\n";
        cin >> leadCardIndex;
        Card leadCard = hands.at(leadCardIndex);
        hands.erase(hands.begin() + leadCardIndex);
        std::sort(hands.begin(), hands.end());
        return leadCard;
    }
    
    Card play_card(const Card &led_card, const std::string &trump) {
        std::sort(hands.begin(), hands.end());
        print_hand();
        int playCardIndex = 0;
        cout << "Human player " << name << ", please select a card:\n";
        cin >> playCardIndex;
        Card playCard = hands.at(playCardIndex);
        hands.erase(hands.begin() + playCardIndex);
        std::sort(hands.begin(), hands.end());
        return playCard;
    }
    
    void print_hand() const {
        for (int i = 0; i < hands.size(); i++) {
            cout << "Human player " << name << "'s hand: " 
            << "[" << i << "] " << hands.at(i) << "\n";
        }
    }
    
};


Player * Player_factory(const std::string &name, 
    const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}