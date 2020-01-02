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
    /**
     * Start method called before game loop
     */
    void start();

    /**
     * Save the visual board as an image and board as a text file
     * @param text text displayed at the bottom of image and text file
     * @param subText subtext displayed below text
     */
    void save(std::string text = "", std::string subText = "");

    /**
     * Handle the visual player input
     */
    void input();

    /**
     * Wait for the user to close the window
     * User can also save with 's'
     * @param text text displayed at the bottom of board
     * @param subText subtext displayed below text
     */
    virtual void wait(std::string text = "", std::string subText = "");

protected :
    VisualBoard vb;                             // the visual board
    const std::string IMGNAME = "screenshot";   // base file name for visual board saves

    /**
     * Initialize visual player with a board
     * @param n player name
     * @param b the board
     * @param autoSave true if autosave board after each valid move
     * @param dname directory name for board saves
     * @param vb the visual board
     */
    VisualPlayer(std::string n, const Board& b, bool autoSave, std::string dname, const VisualBoard& vb);

    /**
     * Create visual board and board from user input
     */
    void createBoard();

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
