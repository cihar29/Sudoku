//
//  technique.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/26/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef technique_hpp
#define technique_hpp

#include "board.hpp"

class Technique {
    bool aNums[Board::N][Board::N][Board::N];   // true if an entry is available at a position on board
    int countNums[Board::N][Board::N];          // count number of available entries per position
    int countRow[Board::N][Board::N],           // available entry count per row
        countCol[Board::N][Board::N],           // available entry count per col
        countSq[Board::N][Board::N];            // available entry count per square
    std::string text;                           // text describing the technique

    /**
     * Decrement the count arrays with c0 in the positions surrounding (i0, j0)
     * @param i0 the row
     * @param j0 the col
     * @param c0 the entry
     */
    void decrementSurrounding(int i0, int j0, int c0);

public :
    /**
     * Initialize the techniques used to solve a Sodoku puzzle
     */
    Technique(const Board& b);

    /**
     * Is entry c available in board at (i, j)?
     * @param i the row
     * @param j the col
     * @param c the entry
     * @return true if c is available at (i, j) in board
     */
    bool isAvailable(int i, int j, char c) const;

    /**
     * Get the text describing the technique
     * @return the text describing the technique
     */
    std::string getText() const;

    /**
     * Insert entry c at (i, j) into board and modify arrays
     * @param b the board
     * @param i the row
     * @param j the col
     * @param c the entry
     * @return true if entry successfully inserted into b
     */
    bool insert(Board* b, int i, int j, int c);

    /**
     * Check if any row has an entry available exactly once
     * @param i0 the available row
     * @param c0 the available entry
     * @return true if entry available once in a row
     */
    bool availableInRow(int* i0, char* c0);

    /**
     * Check if any col has an entry available exactly once
     * @param j0 the available col
     * @param c0 the available entry
     * @return true if entry available once in a col
     */
    bool availableInCol(int* j0, char* c0);
};

#endif /* technique_hpp */
