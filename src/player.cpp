//
//  player.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "player.hpp"

Player::Player(std::string n, std::string fname, bool autoSave) :
NAME(n), dName(""), nSaves(0), forceQuit(false), nMoves(0), b(fname), AUTOSAVE(autoSave) {

}

void Player::getInput(std::string* input) const {
    std::cout << "Row Col Num: ";
    std::getline(std::cin, *input);
}

bool Player::insert(std::string input) {
    return input.length()==5 && b.insert(input[0]-'0', input[2]-'0', input[4]);
}

bool Player::remove() {
    std::cout << "\nRemove a number (type 'q' to go back)" << std::endl;

    std::string input;
    do {
        std::cout << "Row Col: ";
        std::getline(std::cin, input);

        if (input == "q") return false;

    } while (input.length()!=3 || !b.remove(input[0]-'0', input[2]-'0'));

    return true;
}

void Player::createBoard() {
    std::cout << "Create your board\n\n"
              << "Input your own numbers\n"
              << "Type 'r' to remove an entry\n"
              << "Type ' ' to start game\n"
              << "Type 'q' to quit game\n" << std::endl;
    
    // user inputs numbers for board until spacebar or 'q' is hit
    std::string input;
    while (true) {
        b.print();
        do {
            getInput(&input);
            if (input == "q") {
                forceQuit = true;
                return;
            }
            else if (input == " ") return;
            else if (input == "r" && remove())
                b.print();

        } while (!insert(input));
    }
}

void Player::initializeBoard() {
    createBoard();
    b.setInitialBoard();
    b.clearText();
}

Player::Player(std::string n, bool create, bool autoSave) :
NAME(n), dName(""), nSaves(0), forceQuit(false), nMoves(0), b{}, AUTOSAVE(autoSave) {

    if (create) initializeBoard();
}

void Player::mkSaveDir() {
    // S_IRWXU - Read, write, execute/search by owner
    // S_IRWXG - Read, write, execute/search by group
    // S_IROTH - Read permission, others
    // S_IXOTH - Execute/search permission, others
    int i = 0;
    // iterate the name of the directory until we find an unused directory name, and create it
    do {
        i++;
        dName = DBASE + std::to_string(i);
    } while (mkdir(dName.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1);
}

void Player::save(std::string text, std::string subText) {
    // check if we already have a directory
    if (dName.empty()) mkSaveDir();

/*
    // test player hack (save without creating base directory first)
    else if ( dname.find(dbase) == std::string::npos ) {
        std::string d2name = dname; // brute force directory
        mkDir();
        dname += d2name;
        mkdir( dname.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
    }
*/
    nSaves++;
    std::string fname = dName + "/" + FNAME + std::to_string(nSaves) + ".txt";
    b.save(fname, NAME + "'s Board", text, subText);
}

void Player::input() {
    std::cout << "Input move\n\n"
              << "Type 'r' to remove an entry\n"
              << "Type 's' to save board\n"
              << "Type 'q' to quit\n" << std::endl;
    b.print();
    std::string input;
    do {
        getInput(&input);
        if (input == "q") {
            forceQuit = true;
            return;
        }
        else if (input == "s")
            save(b.getText());
        else if (input == "r" && remove()) {
            b.print();
            if (AUTOSAVE) save(b.getText());
        }
    } while (!insert(input));

    if (AUTOSAVE) save(b.getText());
}

void Player::end(bool winner) {
    if (forceQuit) printf("%s\n\n", QUITTEXT.data());
    else {
        b.print();
        printf("%s\n\n", winner?WINTEXT.data():LOSETEXT.data());

        if (AUTOSAVE) {
            if (winner) save(WINTEXT);
            else        save(b.getText(), LOSETEXT);
        }
    }
}

bool Player::play() {
    bool valid = b.isValid();
    if (valid && !forceQuit) {

        std::cout << NAME << " Start!\n" << std::endl;
        while (!b.isFull()) {

            input();
            if (forceQuit) break;
            nMoves++;

            valid = b.isValid();
            if (!valid) break;
        }
    }
    bool winner = valid && b.isFull();
    end(winner);
    return winner;
}

int Player::getNMoves() const {
    return nMoves;
}

Player::~Player() {

}
