//
//  visualCompPlayer.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/29/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef visualCompPlayer_hpp
#define visualCompPlayer_hpp

#include "visualPlayer.hpp"
#include "compPlayer.hpp"

class VisualCompPlayer : public VisualPlayer, public CompPlayer {
    /**
     * Initialize test visual computer player with a board and a technique
     * @param n player name
     * @param b the board
     * @param autoSave true if autosave board after each valid move
     * @param walkThrough true if user works through puzzle step-by-step
     * @param t the technique
     * @param dname directory name for board saves
     * @param vb the visual board
     */
    VisualCompPlayer(std::string n, const Board& b, bool autoSave, bool walkThrough,
                     const Technique& t, std::string dname, const VisualBoard& vb);

    /**
     * Wait for the user to press enter
     * User can also save with 's' or exit using the box at the upper left corner of the window
     * @param text the text for the board save
     * @param subText the subtext for the board save
     */
    void wait(std::string text = "", std::string subText = "");

    /**
     * Start method called before game loop
     */
    void start();

    /**
     * Insert into visual computer player's board and technique
     * @param i the row
     * @param j the col
     * @param c the entry
     * @return true if insert is successful
     */
    bool insert(int i, int j, char c);

    /**
     * Fill the empty positions in this board with the entries in otherB
     * @param otherB the other board
     */
    void insertTheRest(const Board& otherB);

    /**
     * Use a test visual computer player
     * @param i row of initial insert
     * @param j col of initial insert
     * @param c entry of initial insert
     * @return true if test player wins
     */
    bool testPlayer(int i, int j, char c);

    /**
     * Handle the visual computer player input
     */
    void input();

    /**
     * Save the visual board as an image and board as a text file
     * @param text text displayed at the bottom of image and text file
     * @param subText subtext displayed below text
     */
    void save(std::string text = "", std::string subText = "");

    /**
     * Handle the end of the game, including quitting midgame
     * @param winner did visual computer player win?
     */
    void end(bool winner);

public :
    /**
     * Initialize visual computer player with board from file
     * @param n player name
     * @param fname file name
     * @param autoSave true if autosave board after each valid move
     * @param walkThrough true if user works through puzzle step-by-step
     */
    VisualCompPlayer(std::string n, std::string fname, bool autoSave, bool walkThrough);

    /**
     * Initialize visual computer player with empty board
     * @param n player name
     * @param create true if user creates board
     * @param autoSave true if autosave board after each valid move
     * @param walkThrough true if user works through puzzle step-by-step
     */
    VisualCompPlayer(std::string n, bool create, bool autoSave, bool walkThrough);
};

#endif /* visualCompPlayer_hpp */
