//
//  compPlayer.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/26/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "compPlayer.hpp"

CompPlayer::CompPlayer(std::string n, std::string fname, bool autoSave, bool walkThrough, bool test) :
Player(n, fname, autoSave), TEST(test), tech(b), WALKTHROUGH(walkThrough), endTest(false) {

}

CompPlayer::CompPlayer(std::string n, bool create, bool autoSave, bool walkThrough) :
Player(n, create, autoSave), TEST(false), tech(b), WALKTHROUGH(walkThrough), endTest(false) {

}

CompPlayer::CompPlayer(std::string n, const Board& b, bool autoSave,
                       bool walkThrough, const Technique& t, std::string dname) :
Player(n, b, autoSave, dname), TEST(true), tech(t), WALKTHROUGH(walkThrough), endTest(false) {

}

void CompPlayer::wait(std::string text, std::string subText) {
    std::string input;
    do {
        std::cout << "Press enter to continue ('q' to quit): ";
        std::getline(std::cin, input);
        if (input == "q") {
            forceQuit = true;
            return;
        }
        else if (input == "s")
            save(text, subText);
    } while (!input.empty());
}

void CompPlayer::start() {
    Player::start();
    b.print();
    std::string text = STARTTEXT;
    std::string subText = "";
    if (TEST) {
        text = b.getText();
        subText = tech.getText();
    }

    if (AUTOSAVE) save(text, subText);
    if (WALKTHROUGH) wait(text, subText);
}

bool CompPlayer::solve(int* i0, int* j0, char* c0) {
    
    if (tech.availableInRow(i0, c0)) {
        // get corresponding col
        for (int j=0; j<Board::N; j++) {
            if (tech.isAvailable(*i0, j, *c0)) {
                *j0 = j;
                return true;
            }
        }
    }
    else if (tech.availableInCol(j0, c0)) {
        // get corresponding row
        for (int i=0; i<Board::N; i++)
            if (tech.isAvailable(i, *j0, *c0)) {
                *i0 = i;
                return true;
            }
    }
    else if (int k; tech.availableInSq(&k, c0)) {
        // get corresponding row and col
        for (Square sq(k); sq.hasNext(); sq.next()) {
            int i, j;
            sq.getPos(&i, &j);
            if (tech.isAvailable(i, j, *c0)) {
                *i0 = i;
                *j0 = j;
                return true;
            }
        }
    }
    else if (tech.oneAvailable(i0, j0)) {
        // get corresponding entry
        for (char c='1'; c<='9'; c++) {
            if (tech.isAvailable(*i0, *j0, c)) {
                *c0 = c;
                return true;
            }
        }
    }
    // no moves
    return false;
}

bool CompPlayer::insert(int i, int j, char c) {
    if (b.insert(i, j, c)) {
        tech.insert(i, j, c);
        printf("%s\n\n\n", tech.getText().data());
        b.print();
        return true;
    }
    else return false;
}

bool CompPlayer::testPlayer(int i, int j, char c) {
    CompPlayer test("Test " + NAME, b, AUTOSAVE, WALKTHROUGH, tech, dName);

    if (test.forceQuit || !test.insert(i, j, c))
        forceQuit = true;
    else if (test.play()) {
        nMoves += test.getNMoves();
        b = test.b;     // set the winning board
        return true;
    }
    else if (test.forceQuit)
        forceQuit = true;
    
    nMoves += test.getNMoves();
    return false;
}

void CompPlayer::input() {
    int i, j;
    char c;
    if (solve(&i, &j, &c)) {
        if (!insert(i, j, c)) {
            forceQuit = true;
            return;
        }
        std::string techText = tech.getText();
        if (AUTOSAVE) save(b.getText(), techText);
        if (WALKTHROUGH) wait(b.getText(), techText);
    }
    else {
        printf("%s\n\n", NOMOVESTEXT.data());
        if (TEST) {
            endTest = true;
            forceQuit = true;
            return;
        }
        // brute force
        int i, j;
        char c;
        while (tech.nextAvailable(&i, &j, &c))
            if (testPlayer(i, j, c) || forceQuit)
                return;
    }
}

void CompPlayer::save(std::string text, std::string subText) {
    // check if we already have a directory for test player
    if (TEST) {
        if (dName.empty())
            mkSaveDir(DBASE);
        if (dName.find(TESTDBASE) == std::string::npos)
            mkSaveDir(dName + "/" + TESTDBASE);
    }
    Player::save(text, subText);
}

void CompPlayer::end(bool winner) {
    if (TEST) {
        if (endTest) {
            forceQuit = false;
            printf("%s\n\n", ENDTESTTEXT.data());
            if (AUTOSAVE) save(NOMOVESTEXT, ENDTESTTEXT);
            if (WALKTHROUGH) wait(NOMOVESTEXT, ENDTESTTEXT);
        }
    }
    else Player::end(winner);
}
