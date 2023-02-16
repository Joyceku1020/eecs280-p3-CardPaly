// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include <cassert>
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_card_less1) {
    Card c1(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(c1, c2, Card::SUIT_HEARTS));
}

TEST(test_card_less2) {
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(c1, c2, Card::SUIT_HEARTS));
}

TEST(test_card_less3) {
    Card c1(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card ledcard(Card::RANK_EIGHT, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(c1, c2, ledcard, Card::SUIT_HEARTS));
}

TEST(test_default_ctor) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_getrank) {
    Card c(Card::RANK_FIVE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_FIVE);
}

TEST(test_getsuit) {
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_CLUBS);
}

TEST(test_getsuit_leftbower) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);
}

TEST(test_is_face_or_ace) {
    Card c1(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_FALSE(c1.is_face_or_ace());
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(c2.is_face_or_ace());
    Card c3(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(c3.is_face_or_ace());
    Card c4(Card::RANK_KING, Card::SUIT_CLUBS);
    ASSERT_TRUE(c4.is_face_or_ace());
    Card c5(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(c5.is_face_or_ace());
    Card c6(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_FALSE(c6.is_face_or_ace());
}

TEST(test_is_right_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_right_bower(Card::SUIT_HEARTS));
}

TEST(test_is_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_HEARTS));
}

TEST(test_is_trump) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_trump(Card::SUIT_HEARTS));
}

TEST(test_less_operator) {
    Card c1(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<(c2, c1));
}

TEST(test_less_operator_same_rank) {
    Card c1(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(operator<(c1, c2));
}

TEST(test_less_operator_false) {
    Card c1(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator<(c1, c2));
}

TEST(test_less_than_or_equal_to) {
    Card c1(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<=(c2, c1));
}

TEST(test_greater_operator) {
    Card c1(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator>(c2, c1));
}

TEST(test_card_self_comparison) {
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(ace_hearts < ace_hearts);
    ASSERT_TRUE(ace_hearts <= ace_hearts);
    ASSERT_FALSE(ace_hearts > ace_hearts);
    ASSERT_TRUE(ace_hearts >= ace_hearts);
    ASSERT_TRUE(ace_hearts == ace_hearts);
    ASSERT_FALSE(ace_hearts != ace_hearts);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           Card::SUIT_CLUBS));
}

TEST(test_card_insertion) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

// Add more test cases here

TEST_MAIN()
