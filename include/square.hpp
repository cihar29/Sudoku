//
//  square.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef square_hpp
#define square_hpp

#include <math.h>
#include "board.hpp"

class Square {
    const int SRN;   // square root of N where sRN x sRN is size of square within board
    int i;           // current row in board
    int j;           // current col in board
    int nMoves;      // number of moves in square

public :
    /**
     * Initialize a square within board
     * isq 0 corresponds to square (0,0) x (2,2), while
     * isq 8 corresponds to square (6,6) x (8,8) in board
     * @param isq the square number
     */
    Square(int isq);

    /**
     * Initialize a square within board using the row and col of a position within square
     * @param i the row
     * @param j the col
     */
    Square(int i, int j);

    /**
     * Is there another position in the square?
     * @return true if there is another position
     */
    bool hasNext() const;

    /**
     * Set the next position in square
     */
    void next();

    /**
     * Get the position in square
     * @param i the row
     * @param j the col
     */
    void getPos(int* i, int* j);
};

#endif /* square_hpp */
