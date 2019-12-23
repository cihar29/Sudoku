//
//  square.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "square.hpp"

Square::Square(int isq) : SRN(sqrt(Board::N)), i(isq/SRN*SRN), j(isq%SRN*SRN), nMoves(0) {

}

Square::Square(int i, int j) : SRN(sqrt(Board::N)), i(i/SRN*SRN), j(j/SRN*SRN), nMoves(0) {

}

bool Square::hasNext() const {
    return nMoves < Board::N;
}

void Square::next() {
    if (!hasNext()) return;
    nMoves++;
    j++;
    // did we reach end of column?
    if (j % SRN == 0) {
        i++;
        j -= SRN;
    }
}

void Square::getPos(int* i, int* j) {
    *i = this->i;
    *j = this->j;
}
