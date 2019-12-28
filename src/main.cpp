//
//  main.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "player.hpp"
#include "visualPlayer.hpp"
#include "compPlayer.hpp"

int main(int argc, const char * argv[]) {

    // make sure all tests are passed in technique_test
    // allow solving infinitely many solution puzzles (eg completely blank board)
    // better Board::entryToIdx implementation
    // test autosave (especially in visualplayer::end (order of rendering))
    // use more helper methods like red outline movement method, etc; tell the story- what if movement changed?
    // clear helpers in fillBoard method probably when using test player
    // add less hard puzzle to puzzles to demonstrate ease without brute force
    // use googletest
    // tests - every method! (lots to test in technique)
    // make file with better compiler language

    // use run file to choose which type of player and options to use
//    VisualPlayer p("Chuck", std::string("technique_tests/intersect_col.txt"), false);
    CompPlayer p("Chuck", std::string("puzzles/input1.txt"), false, false);
//    CompPlayer p("Chuck", std::string("save3/board1.txt"), false, true);
//    VisualPlayer p("Chuck", std::string("puzzles/input1.txt"), false);
//    VisualPlayer p("Chuck", std::string("save3/board1.txt"), false);
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
