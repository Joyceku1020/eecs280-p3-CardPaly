// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Card.h"
#include "Pack.h"

using namespace std;

class Game {
    public:
    Game(char** argv, int pointstowin) { 
        if(strcmp(argv[2], "noshuffle") == 0) { 
            thisshufflesetting = false;
        }
        else thisshufflesetting = true;
        thispointstowin = pointstowin;
        Player * player0 = Player_factory(argv[4], argv[5]);
        Player * player1 = Player_factory(argv[6], argv[7]);
        Player * player2 = Player_factory(argv[8], argv[9]);
        Player * player3 = Player_factory(argv[10], argv[11]);
        players.push_back(player0);
        players.push_back(player1);
        players.push_back(player2);
        players.push_back(player3);
        curPlayer = players[0];
        dealer = players[0];
        thispointstowin = pointstowin;
    }

    void play() {
        while(true) {
            if (hand == 0) {
                dealer = players[0];
            }
            else {
                dealer = players[0];
                for(int i = 0; i < hand; i++) {
                    dealer = to_left(dealer);
                }
            }
            cout << "Hand " << hand << endl;
            operator<<(cout, *dealer);
            cout << " deals" << endl;
            shuffle();
            curPlayer = dealer;
            //3-2-3-2
            to_left();
            deal(3);
            to_left();
            deal(2);
            to_left();
            deal(3);
            to_left();
            deal(2);
            //2-3-2-3
            to_left();
            deal(2);
            to_left();
            deal(3);
            to_left();
            deal(2);
            to_left();
            deal(3);
            to_left();
            
            Card upcard = pack.deal_one(); //round 1, upcard == trump suit.
            operator<<(cout, upcard);
            order_up_suit = upcard.get_suit();
            cout << " turned up" << endl;
            //round 1 of making
            for(int i = 0; i < 4; i++) {
                make_trump(upcard, curPlayer);
                if(orderedup) {
                    operator<<(cout, *curPlayer);
                    cout << " orders up " << order_up_suit << endl << endl;
                    ordering_up_player = curPlayer;
                    dealer->add_and_discard(upcard);
                    break;
                }
                else {
                    operator<<(cout, *curPlayer);
                    cout << " passes" << endl;
                }
                to_left();
            }
            //if everyone passes, curPlayer is now == dealer
            if(!orderedup) { //run round 2
                round++;
                for(int i = 0; i < 4; i++) {
                    make_trump(upcard, curPlayer);
                    if(orderedup) {
                        operator<<(cout, *curPlayer);
                        cout << " orders up " << order_up_suit << endl << endl;
                        ordering_up_player = curPlayer;
                        break;
                    }
                    else {
                        operator<<(cout, *curPlayer);
                        cout << " passes" << endl;
                    }
                    to_left();
                }
            }
            orderedup = false;
            //round 2 over, tricks may now start
            for(int i = 0; i < 5; i++) {
                if(i == 0) {
                    curPlayer = dealer;
                    to_left();
                }
                c1 = curPlayer->lead_card(order_up_suit);
                p1 = curPlayer;
                operator<<(cout, c1);
                cout << " led by " << *curPlayer << endl;
                to_left();
                c2 = curPlayer->play_card(c1, order_up_suit);
                p2 = curPlayer;
                operator<<(cout, c2);
                cout << " played by " << *curPlayer << endl;
                to_left();
                c3 = curPlayer->play_card(c1, order_up_suit);
                p3 = curPlayer;
                operator<<(cout, c3);
                cout << " played by " << *curPlayer << endl;
                to_left();
                c4 = curPlayer->play_card(c1, order_up_suit);
                p4 = curPlayer;
                operator<<(cout, c4);
                cout << " played by " << *curPlayer << endl;
                to_left();

                cardsPlayed.push_back(c1);
                cardsPlayed.push_back(c2);
                cardsPlayed.push_back(c3);
                cardsPlayed.push_back(c4);

                highest = c1;
                for (int i = 1; i < 4; i++) {
                    if (Card_less(highest, cardsPlayed[i], c1, order_up_suit)) {
                        highest = cardsPlayed[i];
                    }
                }

                
                if (highest == c1) {
                    winnerOfTrick = p1;
                }
                else if (highest == c2) {
                    winnerOfTrick = p2;
                }
                else if (highest == c3) {
                    winnerOfTrick = p3;
                }
                else {
                    winnerOfTrick = p4;
                }


                operator<<(cout, *winnerOfTrick);
                cout << " takes the trick" << endl << endl;


                for (int a = 0; a < 4; a++) {
                    if (players[a] == winnerOfTrick) {
                        if (a == 0 || a == 2) {
                            team1TricksWon++;
                        }
                        else {
                            team2TricksWon++;
                        }
                    }
                }

                dealer = winnerOfTrick;
                curPlayer = winnerOfTrick;
                cardsPlayed.clear();

                for (int j = 0; j < 4; j++) {
                    if (players[j] == curPlayer) {
                        leadingPlayerIndex = j;
                    }
                }
            }
            hand++;

            if (team1TricksWon > team2TricksWon) {
                cout << players[0]->get_name() << " and " << 
                players[2]->get_name() << " win the hand" << endl; 
                if(!(players[0] == ordering_up_player 
                || players[2] == ordering_up_player)) {
                    team1Points += 2;
                    cout << "euchred!" << endl;
                }
                else {
                    if(team1TricksWon == 5) {
                        team1Points += 2;
                        cout << "march!" << endl;
                    }
                    else {
                        team1Points++;
                    }
                }
            }
            else {
                cout << players[1]->get_name() << " and " 
                << players[3]->get_name() << " win the hand" << endl;  ///
                if(!(players[1] == ordering_up_player 
                || players[3] == ordering_up_player)) {  ///
                    team2Points += 2;
                    cout << "euchred!" << endl;
                }
                else {
                    if(team2TricksWon == 5) {
                        team2Points += 2;
                        cout << "march!" << endl;
                    }
                    else {
                        team2Points++;
                    }
                }
            }
            team1TricksWon = 0;
            team2TricksWon = 0;

            

            cout << players[0]->get_name() << " and " 
            << players[2]->get_name() << " have " 
            << team1Points << " points" << endl; 

            cout << players[1]->get_name() << " and " 
            << players[3]->get_name() << " have " 
            << team2Points << " points" << endl << endl; 
            
            if(team1Points >= thispointstowin || team2Points >= thispointstowin) {
                if (team1Points >= thispointstowin) {
                    cout << players[0]->get_name() << " and " 
                    << players[2]->get_name() << " win!" << endl; 
                }
                else {
                    cout << players[1]->get_name() << " and " 
                    << players[3]->get_name() << " win!" << endl;
                }
                game_is_ended = true;
            }
            if(game_is_ended) break;
            //change dealer vvv, set to curPlayer, increase hand iteration, set round = 1.
            round = 1;
        }
    }
    
    private:
    int hand = 0;
    int round = 1;
    bool thisshufflesetting;
    vector<Player*> players;
    Player* curPlayer;
    Player* dealer;
    int leadingPlayerIndex;
    int thispointstowin;
    int team1Points = 0;
    int team2Points = 0;
    int team1TricksWon = 0;
    int team2TricksWon = 0;
    Pack pack;
    string order_up_suit;
    bool orderedup = false;
    bool game_is_ended = false;
    Card highest;
    Card c1;
    Card c2;
    Card c3;
    Card c4;
    Player* p1;
    Player* p2;
    Player* p3;
    Player* p4;
    std::vector<Card> cardsPlayed;
    Player* winnerOfTrick;
    Player* ordering_up_player;


    void shuffle() {
        if(thisshufflesetting == true) pack.shuffle();
        else pack.reset();
    }
    void deal() {
        curPlayer->add_card(pack.deal_one());
    }
    void deal(int numCards) {
        for(int i = 0; i < numCards; i++) {
            deal();
        }
    }
    void make_trump(const Card &upcard, Player * player) {
        if(player->make_trump(upcard, (dealer == player), 
        round, order_up_suit)) { 
            orderedup = true;
        }
    }
    
    bool is_dealer(Player * player) {
        if(player == players[round]) return true;
        return false;
    }
    void to_left() {
        if (curPlayer == players[0]) curPlayer = players[1];
        else if(curPlayer == players[1]) curPlayer = players[2];
        else if(curPlayer == players[2]) curPlayer = players[3];
        else curPlayer = players[0];
    }

    Player* to_left(Player * player) {
        int index = 0;
        for (int i = 0; i < 4; i++) {
            if (player == players[i]) {
                index = i + 1;
            }
        }
        if(index == 4) return players[0];
        return players[index];
    }
};

int main(int argc, char **argv) {
    string fileName = argv[1];

    ifstream fin(fileName);
    ofstream fout;

    if (!fin.is_open()) {
        cout << "Error opening " << fileName << endl;
        return -1;
    }
    fin.close();
    for(int i = 0; i < 12; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    //condition 1
    if(argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return -1;
    }
    int points = atoi(argv[3]);
    //condition 2
    if(points > 100 || points < 1) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return -1;
    }
    // //condition 3
    if(!(strcmp(argv[2], "shuffle") == 0) 
    && !(strcmp(argv[2], "noshuffle") == 0)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return -1;
    }
    // //5, 7, 9, 11, condition 4
    for(int i = 5; i < 12; i+=2) {
        if(!(strcmp(argv[i], "Simple") == 0) 
        && !(strcmp(argv[i], "Human") == 0)) {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
            return -1;
        }
    }
    
    Game game(argv, points);
    game.play();

    return 0;
}