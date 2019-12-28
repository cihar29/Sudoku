//
//  compPlayer.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/26/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "compPlayer.hpp"

CompPlayer::CompPlayer(std::string n, std::string fname, bool autoSave, bool walkThrough) :
Player(n, fname, autoSave), tech(b), WALKTHROUGH(walkThrough) {

}

CompPlayer::CompPlayer(std::string n, bool create, bool autoSave, bool walkThrough) :
Player(n, create, autoSave), tech(b), WALKTHROUGH(walkThrough) {

}

bool CompPlayer::solve() {
    int i, j, k;
    char c;

    if (tech.availableInRow(&i, &c)) {
        // get corresponding col
        for (j=0; j<Board::N; j++)
            if (tech.isAvailable(i, j, c))
                break;
        return tech.insert(&b, i, j, c);
    }
    else if (tech.availableInCol(&j, &c)) {
        // get corresponding row
        for (i=0; i<Board::N; i++)
            if (tech.isAvailable(i, j, c))
                break;
        return tech.insert(&b, i, j, c);
    }
    // else if (tech.availableInSq(&k, &c))
    // else if (tech.oneAvailable(&i, &j, &c))
    // no moves
    else return false;
}

void CompPlayer::input() {
    b.print();

    if (solve()) {
        std::string technique = tech.getText();
        printf("%s\n\n\n", technique.data());

        if (WALKTHROUGH) {
            std::string input;
            do {
                std::cout << "Press enter to continue ('q' to quit): ";
                std::getline(std::cin, input);
                if (input == "q") {
                    forceQuit = true;
                    return;
                }
                else if (input == "s")
                    save(b.getText(), technique);
            } while (!input.empty());
        }
        if (AUTOSAVE) save(b.getText(), technique);
    }
    else {
        printf("%s\n\n", NOMOVESTEXT.data());
        // brute force
        forceQuit = true;   // temporary
    }
}
