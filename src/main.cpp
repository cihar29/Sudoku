//
//  main.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "player.hpp"
#include "visualPlayer.hpp"

int main(int argc, const char * argv[]) {

    // better Board::entryToIdx implementation
    // test autosave
    // use more helper methods like red outline movement method, etc; tell the story- what if movement changed?
    // clear helpers in fillBoard method probably when using test player
    // add less hard puzzle to puzzles to demonstrate ease without brute force
    // use googletest
    // tests
    // make file with better compiler language

    VisualPlayer p("Chuck", std::string("puzzles/input1.txt"), false);
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
