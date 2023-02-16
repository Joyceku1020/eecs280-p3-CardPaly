// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include <cassert>
#include "unit_test_framework.h"
#include "Card.h"
#include <fstream>
#include <iostream>

using namespace std;

static const int PACK_SIZE = 24;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

// Add more tests here
TEST(test_initialize) {
    Pack pack;
    pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, second.get_suit());
}

TEST(test_initialize_input) {
    const string filename = "pack.in";
    ifstream ifs(filename);
    assert(ifs.is_open());
    Pack pack(ifs);
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    Card eighth = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, eighth.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, eighth.get_suit());
}

TEST(test_deal_one) {
    Pack pack;
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    Card fourth = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_QUEEN, fourth.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, fourth.get_suit());
}

TEST(test_reset) {
    Pack pack;
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.reset();
    Card first_card = pack.deal_one();
    ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
}

TEST(test_shuffle) {
    Pack pack;
    pack.shuffle();
    pack.deal_one();
    Card second_card = pack.deal_one();
    ASSERT_EQUAL(second_card, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
}

TEST(test_shuffle2) {
    Pack pack;
    for (int i = 1; i <= 20; i++) {
        pack.shuffle();
    }
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(first, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ASSERT_EQUAL(second, Card(Card::RANK_TEN, Card::SUIT_SPADES));
}

TEST(test_empty_false) {
    Pack pack;
    pack.deal_one();
    ASSERT_FALSE(pack.empty());
}

TEST(test_empty_true) {
    Pack pack;
    for (int i = 0; i < PACK_SIZE - 1; ++i) {
        pack.deal_one();
        ASSERT_FALSE(pack.empty());
    }
    pack.deal_one();
    ASSERT_TRUE(pack.empty());
}

TEST_MAIN()
