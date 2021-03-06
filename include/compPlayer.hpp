//
//  compPlayer.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/26/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef compPlayer_hpp
#define compPlayer_hpp

#include "player.hpp"
#include "technique.hpp"

// virtual needed to solve diamond inheritance problem presented to subclass of CompPlayer
class CompPlayer : virtual public Player {
    const std::string TESTDBASE = "test";   // base directory name for test board saves

    /**
     * Wait for the user to press enter
     * User can also save with 's' or exit with 'q'
     * @param text the text for the board save
     * @param subText the subtext for the board save
     */
    virtual void wait(std::string text = "", std::string subText = "");

    /**
     * Insert into computer player's board and technique
     * @param i the row
     * @param j the col
     * @param c the entry
     * @return true if insert is successful
     */
    virtual bool insert(int i, int j, char c);

    /**
     * Use a test computer player
     * @param i row of initial insert
     * @param j col of initial insert
     * @param c entry of initial insert
     * @return true if test player wins
     */
    virtual bool testPlayer(int i, int j, char c);

    /**
     * Handle the end of the game, including quitting midgame
     * @param winner did computer player win?
     */
    void end(bool winner);

protected :
    const bool WALKTHROUGH;                             // true if user works through puzzle step-by-step
    const std::string NOMOVESTEXT = "No moves found";   // no moves found text
    const std::string ENDTESTTEXT = "End test";         // end test text
    Technique tech;                                     // technique used to solve puzzle
    const bool TEST;                                    // true if this is a test computer player
    bool endTest;                                       // true if test is over

    /**
     * Initialize test computer player with a board and a technique
     * @param n player name
     * @param b the board
     * @param autoSave true if autosave board after each valid move
     * @param walkThrough true if user works through puzzle step-by-step
     * @param t the technique
     * @param dname directory name for board saves
     */
    CompPlayer(std::string n, const Board& b, bool autoSave, bool walkThrough, const Technique& t, std::string dname);

    /**
     * Start method called before game loop
     */
    void start();

    /**
     * Calculate the move to solve a Sodoku puzzle using a technique
     * @param i0 the row calculated
     * @param j0 the col calculated
     * @param c0 the entry calculated
     * @return true if move calculated
     */
    bool solve(int* i0, int* j0, char* c0);

    /**
     * Save the board as a text file
     * Take care to use the correct directory for test players
     * @param text text displayed at the bottom of file
     * @param subText subtext displayed below text
     */
    void save(std::string text = "", std::string subText = "");

    /**
     * Handle the computer player input
     */
    void input();

public :
    /**
     * Initialize computer player with board from file
     * @param n player name
     * @param fname file name
     * @param autoSave true if autosave board after each valid move
     * @param walkThrough true if user works through puzzle step-by-step
     * @param test is this a test player (i.e. don't attempt brute force)?
     */
    CompPlayer(std::string n, std::string fname, bool autoSave, bool walkThrough, bool test);

    /**
     * Initialize computer player with empty board
     * @param n player name
     * @param create true if user creates board
     * @param autoSave true if autosave board after each valid move
     * @param walkThrough true if user works through puzzle step-by-step
     */
    CompPlayer(std::string n, bool create, bool autoSave, bool walkThrough);
};

#endif /* compPlayer_hpp */
