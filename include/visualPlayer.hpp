//
//  visualPlayer.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/20/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef visualPlayer_hpp
#define visualPlayer_hpp

#include "player.hpp"
#include "visualBoard.hpp"

// virtual needed to solve diamond inheritance problem presented to subclass of VisualPlayer
class VisualPlayer : virtual public Player {
    const std::string IMGNAME = "screenshot";   // base file name for visual board saves

    /**
     * Handle the visual player input
     */
    void input();

protected :
    VisualBoard vb;                                    // the visual board

    /**
     * Initialize visual player with a board
     * @param n player name
     * @param b the board
     * @param autoSave true if autosave board after each valid move
     * @param dname directory name for board saves
     */
    VisualPlayer(std::string n, const Board& b, bool autoSave, std::string dname);

    /**
     * Add text and render board before starting game
     * @param text text to render
     * @param subText subtext to render
     */
    void start(std::string text, std::string subText);

    /**
     * Create visual board and board from user input
     */
    void createBoard();

    /**
     * Save the visual board as an image and board as a text file
     * @param text text displayed at the bottom of image and text file
     * @param subText subtext displayed below text
     */
    void save(std::string text = "", std::string subText = "");

    /**
     * Wait for the user to press enter
     * User can also save with 's' or exit using the box at the upper left corner of the window
     * @param text the text for the board save
     * @param subText the subtext for the board save
     */
    void waitForEnter(std::string text = "", std::string subText = "");

    /**
     * Handle the end of the game, including quitting midgame
     * @param winner did player win?
     */
    void end(bool winner);

public :
    /**
     * Initialize visual player with board from file
     * @param n player name
     * @param fname file name
     * @param autoSave true if autosave board after each valid move
     */
    VisualPlayer(std::string n, std::string fname, bool autoSave);

    /**
     * Initialize visual player with empty board
     * @param n player name
     * @param create true if user creates board
     * @param autoSave true if autosave board after each valid move
     */
    VisualPlayer(std::string n, bool create, bool autoSave);
};

#endif /* visualPlayer_hpp */
