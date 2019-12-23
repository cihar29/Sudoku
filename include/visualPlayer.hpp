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
     * Add text and render board before starting game
     */
    void start();

    /**
     * Handle the visual player input
     */
    void input();

protected :
    VisualBoard vb;     // the visual board

    /**
     * Create visual board and board from user input
     */
    void createBoard();

    /**
     * Save the visual board as an image and board as a text file
     * @param text text displayed at the bottom of image and text file
     * @param subText subText displayed below text
     */
    virtual void save(std::string text = "", std::string subText = "");

    /**
     * Handle the end of the game, including quitting midgame
     * @param winner did player win?
     */
    virtual void end(bool winner);

public :
    /**
     * Initialize visual player with board from file
     * @param n player name
     * @param fname file name
     * @param asave true if autosave board after each valid move
     */
    VisualPlayer(std::string n, std::string fname, bool asave);

    /**
     * Initialize visual player with empty board
     * @param n player name
     * @param create true if user creates board
     * @param asave true if autosave board after each valid move
     */
    VisualPlayer(std::string n, bool create, bool asave);
};

#endif /* visualPlayer_hpp */
