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
    /**
     * Handle the computer player input
     */
    void input();

protected :
    const bool WALKTHROUGH;                             // true if user works through puzzle step-by-step
    const std::string NOMOVESTEXT = "No moves found";   // no moves found text
    Technique tech;                                     // technique used to solve puzzle

    /**
     * Make a move to solve a Sodoku puzzle using a technique
     * @return true if move made
     */
    bool solve();

public :
    /**
     * Initialize computer player with board from file
     * @param n player name
     * @param fname file name
     * @param autoSave true if autosave board after each valid move
     * @param walkThrough true if user works through puzzle step-by-step
     */
    CompPlayer(std::string n, std::string fname, bool autoSave, bool walkThrough);

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
