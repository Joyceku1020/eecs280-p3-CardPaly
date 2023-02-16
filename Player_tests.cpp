// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>
#include <cassert>

using namespace std;

TEST(test_player_insert) {
    Player * human = Player_factory("NotRobot", "Human");

    ostringstream oss1;
    oss1 << * human;

    ASSERT_EQUAL(oss1.str(), "NotRobot");

    Player * alice = Player_factory("Alice", "Simple");

    ostringstream oss2;
    oss2 << *alice;
    ASSERT_EQUAL(oss2.str(), "Alice");

    delete human;
    delete alice;
}

TEST(test_player_get_name) {
    Player * joyce = Player_factory("Joyce", "Simple");
    ASSERT_EQUAL("Joyce", joyce->get_name());

    delete joyce;
}

// Add more tests here
TEST(test_add_card) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    Card ledcard(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c = joyce->play_card(ledcard, Card::SUIT_HEARTS);

    Card addedCard(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(addedCard, c);

    delete joyce;
}

TEST(test_make_trump_round_one_true) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card upcard(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trump = "";
    bool orderup = joyce->make_trump(upcard, false, 1, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

    delete joyce;
}

TEST(test_make_trump_round_one_false1) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card upcard(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trump = "";
    bool orderup = joyce->make_trump(upcard, false, 1, trump);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, "");

    delete joyce;
}

TEST(test_make_trump_round_one_false2) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card upcard(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trump = "";
    bool orderup = joyce->make_trump(upcard, false, 1, trump);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, "");

    delete joyce;
}


TEST(make_trump_round_two_true) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card upcard(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trump = "";
    bool orderup = joyce->make_trump(upcard, false, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    delete joyce;
}

TEST(make_trump_round_two_false) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card upcard(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trump = "";
    bool orderup = joyce->make_trump(upcard, false, 2, trump);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, "");

    delete joyce;
}

TEST(make_trump_round_two_dealer) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card upcard(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trump = "";
    bool orderup = joyce->make_trump(upcard, true, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    delete joyce;
}

TEST(test_add_and_discard) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    joyce->add_and_discard(c);

    delete joyce;
}

TEST(test_add_and_discard2) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    joyce->add_and_discard(c);

    delete joyce;
}

TEST(test_lead_card) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card c1(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c2 = joyce->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(c1, c2);

    delete joyce;
}

TEST(test_add_remove_lead_card) {
  Player * joyce = Player_factory("Joyce", "Simple");
  joyce->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  joyce->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  joyce->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  joyce->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  
  joyce->add_and_discard(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  Card card_led = joyce->lead_card(Card::SUIT_HEARTS);

  Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_led, ace_diamonds); 

  delete joyce;
}


TEST(test_lead_card_all_trump) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    Card c1(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2 = joyce->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(c1, c2);

    delete joyce;
}

TEST(test_play_card) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    joyce->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Card ledCard(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c1(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c2 = joyce->play_card(ledCard, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c1, c2);

    delete joyce;
}

TEST(test_play_card_no_ledcard) {
    Player * joyce = Player_factory("Joyce", "Simple");
    joyce->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    joyce->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    joyce->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    joyce->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    Card ledCard(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2 = joyce->play_card(ledCard, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c1, c2);

    delete joyce;
}


TEST_MAIN()
