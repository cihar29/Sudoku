//
//  main.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "visualCompPlayer.hpp"

int main(int argc, const char * argv[]) {

    // make save text better on visual board (not take over everything)
    // make sure all tests are passed in technique_test (add more technique methods)
    // add less hard puzzle to puzzles to demonstrate ease without brute force
    // tests - every method! (lots to test in technique)
    // make file with better compiler language
    // use run file to choose which type of player and options to use
    
//    Player p("Chuck", std::string("puzzles/input1.txt"), false);
//    Player p("Chuck", true, false);
//    CompPlayer p("Chuck", std::string("puzzles/input1.txt"), true, false, false);
//    CompPlayer p("Chuck", true, false, true);
//    VisualPlayer p("Chuck", std::string("puzzles/input1.txt"), false);
//    VisualPlayer p("Chuck", true, false);
    VisualCompPlayer p("Chuck", std::string("puzzles/input1.txt"), true, false);
//    VisualCompPlayer p("Chuck", true, false, true);

    p.play();
    return 0;
}
