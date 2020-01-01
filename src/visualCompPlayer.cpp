//
//  visualCompPlayer.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/29/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "visualCompPlayer.hpp"

VisualCompPlayer::VisualCompPlayer(std::string n, std::string fname, bool autoSave, bool walkThrough) :
Player(n, fname, autoSave), VisualPlayer(n, fname, autoSave), CompPlayer(n, fname, autoSave, walkThrough) {

    start(STARTTEXT, "Press enter to continue");
}

VisualCompPlayer::VisualCompPlayer(std::string n, bool create, bool autoSave, bool walkThrough) :
Player(n, false, autoSave), VisualPlayer(n, create, autoSave), CompPlayer(n, create, autoSave, walkThrough) {

    start(STARTTEXT, "Press enter to continue");
}

VisualCompPlayer::VisualCompPlayer(std::string n, const Board& b, bool autoSave,
                                   bool walkThrough, const Technique& t, std::string dname) :
Player(n, b, autoSave, dname), VisualPlayer(n, b, autoSave, dname),
CompPlayer(n, b, autoSave, walkThrough, t, dname) {

    start(STARTTEXT, "Press enter to continue");
}

void VisualCompPlayer::start(std::string text, std::string subText) {
    VisualPlayer::start(text, subText);
    if (WALKTHROUGH) VisualPlayer::waitForEnter(text);
}

bool VisualCompPlayer::insert(int i, int j, char c, std::string text) {
    vb.setInsert(i, j, c);
    if (vb.insert(&b)) {
        tech.insert(i, j, c);
        printf("%s\n\n\n", text.data());
        b.print();

        vb.setText(b.getText(), text);
        vb.render();
        if (AUTOSAVE) save(b.getText(), text);
        return true;
    }
    else return false;
}

void VisualCompPlayer::input() {
    if (WALKTHROUGH)
        std::cout << "Press enter to continue\n"
                  << "Press 's' to save board\n"
                  << "Click the box at the upper left corner of the window to quit game\n" << std::endl;
    int i, j;
    char c;
    if (solve(&i, &j, &c)) {

        std::string techText = tech.getText();
        if (!insert(i, j, c, techText)) {
            forceQuit = true;
            return;
        }
        if (WALKTHROUGH) VisualPlayer::waitForEnter(b.getText(), techText);
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
        while (tech.nextAvailable(&i, &j, &c)) {
            VisualCompPlayer test("Test " + NAME, b, AUTOSAVE, WALKTHROUGH, tech, dName);

            if (test.forceQuit || !test.insert(i, j, c, tech.getText())) {
                forceQuit = true;
                return;
            }
            else if (test.play()) {
                nMoves += test.getNMoves();
                b = test.b;     // set the winning board
                return;
            }
            else if (test.forceQuit) {
                forceQuit = true;
                return;
            }
            nMoves += test.getNMoves();
        }
    }
}

void VisualCompPlayer::save(std::string text, std::string subText) {
    
}

void VisualCompPlayer::end(bool winner) {
    
}
