//
//  player.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <string>
#include <iostream>
#include <sys/stat.h>
#include "board.hpp"

class Player {
    /**
     * Get the user input
     * @param input the user input
     */
    void getInput(std::string* input) const;

    /**
     * Handle input to insert entry into board
     * @param input the user input
     * @return true if entry inserted
     */
    bool insert(std::string input);

    /**
     * Handle input to remove entry from board
     * @return true if entry removed
     */
    bool remove();

    /**
     * Handle the player input
     */
    virtual void input();

protected :
    const std::string NAME;                 // player name
    const std::string STARTTEXT
        = NAME + " Start!";                 // starting text
    const std::string WINTEXT
        = "Congrats " + NAME + "!!!";       // winning text
    const std::string LOSETEXT
        = "Game over :(";                   // losing text
    const std::string QUITTEXT = "quit";    // quitting text
    const bool AUTOSAVE;                    // true if autosave board after each valid move
    Board b;                                // player board
    bool forceQuit;                         // true if user exits midgame
    const std::string DBASE = "save";       // base directory name for board saves
    const std::string FNAME = "board";      // base file name for board saves
    std::string dName;                      // directory name for board saves
    int nSaves;                             // number of board saves
    int nMoves;                             // number of valid moves player makes

    /**
     * Initialize player with a board
     * @param n player name
     * @param b the board
     * @param autoSave true if autosave board after each valid move
     * @param dname directory name for board saves
     */
    Player(std::string n, const Board& b, bool autoSave, std::string dname);

    /**
     * Create board from user input
     */
    virtual void createBoard();

    /**
     * Initialize the board
     */
    void initializeBoard();

    /**
     * Make directory for board saves
     * @param base the base directory name
     */
    void mkSaveDir(std::string base);

    /**
     * Save the board as a text file
     * @param text text displayed at the bottom of file
     * @param subText subtext displayed below text
     */
    virtual void save(std::string text = "", std::string subText = "");

    /**
     * Handle the end of the game, including quitting midgame
     * @param winner did player win?
     */
    virtual void end(bool winner);

public :
    /**
     * Initialize player with board from file
     * @param n player name
     * @param fname file name
     * @param autoSave true if autosave board after each valid move
     */
    Player(std::string n, std::string fname, bool autoSave);
    
    /**
     * Initialize player with empty board
     * @param n player name
     * @param create true if user creates board
     * @param autoSave true if autosave board after each valid move
     */
    Player(std::string n, bool create, bool autoSave);

    /**
     * Play Sudoku
     * @return true if player wins game
     */
    bool play();

    /**
     * Return number of valid player moves
     * @return number of valid moves
     */
    int getNMoves() const;

    /**
     * Handle destructing player
     * Must be virtual to handle sub class destructors
     */
    virtual ~Player();
};

#endif /* player_hpp */
