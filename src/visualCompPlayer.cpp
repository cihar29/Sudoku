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

}

VisualCompPlayer::VisualCompPlayer(std::string n, bool create, bool autoSave, bool walkThrough) :
Player(n, false, autoSave), VisualPlayer(n, create, autoSave), CompPlayer(n, create, autoSave, walkThrough) {

}

VisualCompPlayer::VisualCompPlayer(std::string n, const Board& b, bool autoSave, bool walkThrough,
                                   const Technique& t, std::string dname, const VisualBoard& vb) :
Player(n, b, autoSave, dname), VisualPlayer(n, b, autoSave, dname, vb),
CompPlayer(n, b, autoSave, walkThrough, t, dname) {

}

void VisualCompPlayer::wait(std::string text, std::string subText) {
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {
                forceQuit = true;
                return;
            }
            // save board
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s) {
                save(text, subText);
                vb.render();
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
                return;
        }
    }
}

void VisualCompPlayer::start() {
    std::string text = STARTTEXT;
    std::string subText = "Press enter to continue";
    if (TEST) {
        text = b.getText();
        subText = tech.getText();
    }

    vb.setText(text, subText);
    vb.render();
    CompPlayer::start();
}

bool VisualCompPlayer::insert(int i, int j, char c, std::string text) {
    vb.setInsert(i, j, c);
    if (vb.insert(&b)) {
        tech.insert(i, j, c);
        printf("%s\n\n\n", text.data());
        b.print();

        vb.setText(b.getText(), text);
        vb.render();
        return true;
    }
    else return false;
}

bool VisualCompPlayer::testPlayer(int i, int j, char c) {
    VisualCompPlayer test("Test " + NAME, b, AUTOSAVE, WALKTHROUGH, tech, dName, vb);

    if (test.forceQuit || !test.insert(i, j, c, tech.getText()))
        forceQuit = true;
    else if (test.play()) {
        nMoves += test.getNMoves();
        b = test.b;     // set the winning board
        //vb.copy(test.vb);
        vb.setTitle(NAME);
        return true;
    }
    else if (test.forceQuit)
        forceQuit = true;
    
    nMoves += test.getNMoves();
    return false;
}

void VisualCompPlayer::input() {
    if (WALKTHROUGH)
        std::cout << "Press enter to continue\n"
                  << "Press 's' to save board\n"
                  << "Click the box at the upper left corner of the window to quit game\n" << std::endl;

    CompPlayer::input();
}

void VisualCompPlayer::save(std::string text, std::string subText) {
    CompPlayer::save(text, subText);
    std::string fname = dName + "/" + IMGNAME + std::to_string(nSaves) + ".png";
    vb.save(fname);
    b.clearText();
    vb.setText("", " ");
    // SDL_Delay(300);
}

void VisualCompPlayer::end(bool winner) {
    if (TEST) {
        if (endTest) {
            forceQuit = false;
            printf("%s\n\n", ENDTESTTEXT.data());
            vb.setText(NOMOVESTEXT, ENDTESTTEXT);
            vb.render();
            if (AUTOSAVE) save(NOMOVESTEXT, ENDTESTTEXT);
            if (WALKTHROUGH) wait();
        }
    }
    else VisualPlayer::end(winner);
}
