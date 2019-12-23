//
//  visualPlayer.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/20/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "visualPlayer.hpp"

void VisualPlayer::start() {
    std::string subText = AUTOSAVE?"Autosave enabled":"";
    vb.setText(NAME + " Start!", subText);
    vb.render();
}

VisualPlayer::VisualPlayer(std::string n, std::string fname, bool asave) : Player(n, fname, asave), vb(b, n) {
    start();
}

void VisualPlayer::createBoard() {
    std::cout << "Create your board\n\n"
              << "Type your own numbers\n"
              << "Use backspace to remove an entry\n"
              << "Press the spacebar to start game\n"
              << "Click the box at the upper left corner of the window to quit game\n" << std::endl;
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {
                forceQuit = true;
                return;
            }
            // start
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
                return;
            // insert entry
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && vb.insert(&b))
                b.print();
            // remove entry
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && vb.remove(&b))
                b.print();
            // other events
            else
                vb.handleEvent(e);

            vb.setText(b.getText(), "Create your board (Press 'space' to start game)");
            vb.render();
        }
    }
}

VisualPlayer::VisualPlayer(std::string n, bool create, bool asave) : Player(n, false, asave), vb(b, n) {
    if (create) {
        initializeBoard();
        vb.fillBoard(b);
        if (forceQuit) return;
        start();
    }
}

void VisualPlayer::save(std::string text, std::string subText) {
    Player::save(text, subText);
    std::string fname = dName + "/" + IMGNAME + std::to_string(nSaves) + ".png";
    vb.save(fname);
    b.clearText();
    vb.setText("", " ");
}

void VisualPlayer::input() {
    std::cout << "Input move\n\n"
              << "Use backspace to remove an entry\n"
              << "Press 's' to save board\n"
              << "Click the box at the upper left corner of the window to quit game\n" << std::endl;
    b.print();
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {
                forceQuit = true;
                return;
            }
            // insert entry
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && vb.insert(&b)) {
                if (AUTOSAVE) save(b.getText());
                return;
            }
            // remove entry
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && vb.remove(&b)) {
                b.print();
                if (AUTOSAVE) save(b.getText());
            }
            // save board
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s)
                save(b.getText());
            // other events
            else {
                vb.handleEvent(e);
                if (vb.handleHelpers(b, e)) {
                    b.clearText();
                    vb.setText("", " ");
                }
            }
            // once we get a text from the board, erase subText
            if (!b.getText().empty())
                vb.setText("", " ");

            vb.setText(b.getText());
            vb.render();
        }
    }
}

void VisualPlayer::end(bool winner) {
    if (forceQuit) printf("%s\n\n", QUITTEXT.data());
    else {
        b.print();
        printf("%s\n\n", winner?WINTEXT.data():LOSETEXT.data());

        std::string text = winner?WINTEXT:b.getText();
        std::string subText = winner?"":LOSETEXT;

        vb.setText(text, subText);
        vb.render();
        if (AUTOSAVE) save(text, subText);

        // wait for player to close window
        SDL_Event e;
        while (e.type != SDL_QUIT) {
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s)
                save(text, subText);
            vb.render();
        }
    }
    vb.clear();
}
