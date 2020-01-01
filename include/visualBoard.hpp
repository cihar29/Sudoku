//
//  visualBoard.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef visualBoard_hpp
#define visualBoard_hpp

#include <vector>
#include "visual.hpp"
#include "visualText.hpp"
#include "board.hpp"
#include "helpingNumbers.hpp"

class VisualBoard : public Visual {
    Screen s;                               // the screen to draw on
    const static int NLINES
        = 2*(Board::N+1);                   // number of board lines
    SDL_Rect lines[NLINES];                 // board lines
    VisualText title, text, subText;        // title, text, and subtext for the visual board
    VisualText nums[Board::N][Board::N];    // array of Sudoku numbers
    VisualText rNum;                        // the number (could be any color) highlighted in red at rPos
    SDL_Point rPos, gPos;                   // red and gold outline positions
    std::vector<SDL_Point>
        vOutlinePos[Board::N];              // positions of the outlined numbers per number
    helpingNumbers helpers;                 // collection of helping numbers on Sudoku board

    /**
     * Is the position on onscreen?
     * @param p the position
     * @return true if p is not offscreen
     */
    bool isOnscreen(const SDL_Point& p) const;

    /**
     * Define the red outline position movement on the board
     * @param e the event containing keyboard input
     * @return true if rPos moves
     */
    bool rPosMovement(const SDL_Event& e);

public :
    /**
     * Initialize visual board
     * @param b the board
     * @param t the title
     */
    VisualBoard(const Board& b, std::string t);

    /**
     * Set the title of the visual board
     * @param t the title
     */
    void setTitle(std::string t);

    /**
     * Fill the visual board with contents of board b
     * @param b the board
     */
    void fillBoard(const Board& b);

    /**
     * Set the text and subtext for the visual board
     * @param t1 text displayed at the bottom of board
     * @param t2 subText displayed below text
     */
    void setText(std::string t1, std::string t2 = "");

    /**
     * Insert rNum into the visual board
     * @param b the board
     * @return true if successfully inserted
     */
    bool insert(Board* b);

    /**
     * remove a number at rPos from the visual board
     * @param b the board
     * @return true if successfully removed
     */
    bool remove(Board* b);

    /**
     * handle mouse motion and keyboard input using rNum, rPos, and gPos
     * @param e the event containing mouse motion or keyboard input
     */
    void handleEvent(const SDL_Event& e);

    /**
     * handle helping number events
     * @param b the board
     * @param e the event containing keyboard input
     * @return true if we have text to display on the visual board
     */
    bool handleHelpers(const Board& b, const SDL_Event& e);

    /**
     * Draw the board on the screen
     */
    void render();

    /**
     * Save the visual board as an image
     * @param fname the file name
     */
    void save(std::string fname);

    /**
     * Set rNum and rPos to prepare for insert
     * @param i the row for rPos
     * @param j the col for rPos
     * @param c the entry for rNum
     */
    void setInsert(int i, int j, char c);

    /**
     * Clear the visual board
     */
    void clear();
};

#endif /* visualBoard_hpp */
