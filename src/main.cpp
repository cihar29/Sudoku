//
//  main.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "visualCompPlayer.hpp"

int main(int argc, const char * argv[]) {

    // what's going on with visualboard::copy?
    // make save text better (not take over everything)
    // make sure all tests are passed in technique_test (add more techniques)
    // add less hard puzzle to puzzles to demonstrate ease without brute force
    // use googletest
    // tests - every method! (lots to test in technique)
    // make file with better compiler language
    // use run file to choose which type of player and options to use
    
//    Player p("Chuck", std::string("puzzles/input1.txt"), false);
//    Player p("Chuck", true, false);
//    CompPlayer p("Chuck", std::string("puzzles/input1.txt"), true, false);
//    CompPlayer p("Chuck", true, false, true);
//    VisualPlayer p("Chuck", std::string("puzzles/input1.txt"), false);
//    VisualPlayer p("Chuck", true, false);
    VisualCompPlayer p("Chuck", std::string("puzzles/input1.txt"), true, false);
//    VisualCompPlayer p("Chuck", true, false, true);

    p.play();
    return 0;

    // test add all with empty board and regular board, save and compare

    //////put these tests somewhere
    for (int i=0; i<Board::N; i++) {
        for (int j=0; j<Board::N; j++) {
            Square s(i, j);
            int i0, j0;
            s.getPos(&i0, &j0);
            printf("(%i, %i) starts at (%i, %i)\n", i, j, i0, j0);
        }
    }
    return 0;

    Board b{};
    for (int k=0; k<Board::N; k++) {
        char c = '1';
        for (Square sq(k); sq.hasNext(); sq.next()) {
            int i, j;
            sq.getPos(&i, &j);
            b.insert(i, j, c);
            b.print();
            b.save("test.txt");
            c++;
        }
    }
    return 0;
}
