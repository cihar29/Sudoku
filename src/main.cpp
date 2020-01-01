//
//  main.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "visualCompPlayer.hpp"

int main(int argc, const char * argv[]) {

    // play method needs to have a virtual initialize method (instead of putting these start methods in constructor)!
    // obviously test gameplay for all four types (and corresponding save/autosave)
    // for visual board, don't make a copy - instead use same board and fillBoard method
    // check gpos and rpos after creating board for visualcompplayer (saves and autosaves too)
    // make sure all tests are passed in technique_test (add more techniques)
    // test autosave (especially in visualplayer::end (order of rendering))
    // add less hard puzzle to puzzles to demonstrate ease without brute force
    // use googletest
    // tests - every method! (lots to test in technique)
    // make file with better compiler language

    // use run file to choose which type of player and options to use
//    VisualCompPlayer p("Chuck", true, false, true);
//    VisualCompPlayer p("Chuck", std::string("puzzles/input1.txt"), false, true);
    CompPlayer p("Chuck", std::string("puzzles/input1.txt"), true, false);
//    VisualPlayer p("Chuck", std::string("puzzles/input1.txt"), false);
//    VisualPlayer p("Chuck", true, false);
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
