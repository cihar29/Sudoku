//
//  helpingNumbers.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/21/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef helpingNumbers_hpp
#define helpingNumbers_hpp

#include <vector>
#include "visual.hpp"
#include "visualText.hpp"
#include "board.hpp"

class helpingNumbers : public Visual {
    const SDL_Color COLOR;                              // color of the numbers
    const SDL_Color LINECOLOR;                          // color of number outlines
    const float SIZE;                                   // size of the numbers
    const int SRN;                                      // the square root of N
    std::vector<VisualText> vNums[Board::N][Board::N];  // array of helping numbers per board position
    std::vector<SDL_Point> vOutlinePos[Board::N];       // positions of the outlined helping numbers per number

    /**
     * Get the position of a helping number on screen
     * @param pos the position of the row and col on board
     * @param i the row
     * @param j the col
     */
    SDL_Point getPos(const SDL_Point& pos, int i, int j) const;

public :
    /**
     * Initialize the collection of helping numbers
     * @param c number color
     * @param lineColor line color
     * @param s size
     */
    helpingNumbers(const SDL_Color& c, const SDL_Color& lineColor, float s);

    /**
     * Add helping number to the screen
     * @param pos the position of the row and col on board
     * @param c the entry
     * @param b the board
     * @param s the screen
     * @param text the error message
     * @return true if added successfully
     */
    bool add(const SDL_Point& pos, char c, const Board& b, const Screen& s, std::string* text);

    /**
     * Remove helping number at pos from screen
     * @param pos the position on the screen
     * @param s the screen
     */
    void remove(const SDL_Point& pos, const Screen& s);

    /**
     * Add all helping numbers to the board
     * @param b the board
     * @param s the screen
     */
    void addAll(const Board& b, const Screen& s);

    /**
     * Draw the helping numbers on the screen
     */
    void renderNums(const Screen& s);

    /**
     * Draw the outlines of the helping numbers on the screen
     * @param idx the index of the outlines to access
     */
    void renderOutlines(const Screen& s, int idx);

    /**
     * Clear the helping numbers
     */
    void clear();
/*
    //rearrange small nums after removal; pass board coordinates of small nums and iterator of first small num to rearrange
    void rearrangeSmallNums( int i, int j, std::vector<VisualChar>::iterator it, const Screen& s );
    */
};

#endif /* helpingNumbers_hpp */
