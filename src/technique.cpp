//
//  technique.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/26/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "technique.hpp"

Technique::Technique(const Board& b) : aNums{false}, countNums{0}, countRow{0}, countCol{0}, countSq{0} {

    // mark entries in each row, col, and square
    bool rows[Board::N][Board::N] = {false}, cols[Board::N][Board::N] = {false}, sqs[Board::N][Board::N] = {false};
    for (int k=0; k<Board::N; k++) {

        for (int j=0; j<Board::N; j++) {
            char c = b.at(k, j);
            if (c == Board::BLANK) continue;
            int idx = b.entryToIdx(c);
            rows[k][idx] = true;
        }

        for (int i=0; i<Board::N; i++) {
            char c = b.at(i, k);
            if (c == Board::BLANK) continue;
            int idx = b.entryToIdx(c);
            cols[k][idx] = true;
        }

        for (Square sq(k); sq.hasNext(); sq.next()) {
            int i, j;
            sq.getPos(&i, &j);
            char c = b.at(i, j);
            if (c == Board::BLANK) continue;
            int idx = b.entryToIdx(c);
            sqs[k][idx] = true;
        }
    }
    // loop over squares, hitting every row and col
    for (int k=0; k<Board::N; k++) {
        for (Square sq(k); sq.hasNext(); sq.next()) {
            int i, j;
            sq.getPos(&i, &j);
            if (b.at(i, j) != Board::BLANK) continue;

            // look at available (false) entries in ith row, jth col, and kth square
            for (int idx=0; idx<Board::N; idx++) {
                if (!rows[i][idx] && !cols[j][idx] && !sqs[k][idx]) {
                    aNums[i][j][idx] = true;
                    countNums[i][j]++;
                    countRow[i][idx]++;
                    countCol[j][idx]++;
                    countSq[k][idx]++;
                }
            }
        }
    }
}

bool Technique::isAvailable(int i, int j, char c) const {
    return aNums[i][j][Board::entryToIdx(c)];
}

std::string Technique::getText() const {
    return text;
}

void Technique::decrement(int i, int j, int idx) {
    aNums[i][j][idx] = false;
    countRow[i][idx]--;
    countCol[j][idx]--;
    countSq[Board::getSquareNumber(i, j)][idx]--;
    countNums[i][j]--;
}

void Technique::decrementSurrounding(int i0, int j0, char c0) {
    int idx = Board::entryToIdx(c0);
    // check row i0
    for (int j=0; j<Board::N; j++)
        if (aNums[i0][j][idx])
            decrement(i0, j, idx);

    // check col j0
    for (int i=0; i<Board::N; i++)
        if (aNums[i][j0][idx])
            decrement(i, j0, idx);

    // check square surrounding (i0, j0)
    for (Square sq(i0, j0); sq.hasNext(); sq.next()) {
        int i, j;
        sq.getPos(&i, &j);
        if (aNums[i][j][idx])
            decrement(i, j, idx);
    }
    // put this in test
    // countRow[i0][idx] = 0;
    // countCol[j0][idx] = 0;
    // countSq[Board::getSquareNumber(i0, j0)][idx] = 0;
}

void Technique::insert(int i, int j, char c) {
    // other numbers are now unavailable at this position
    for (int idx=0; idx<Board::N; idx++) {
        if (aNums[i][j][idx])
            decrement(i, j, idx);
    }
    // put this in test countNums[i][j] = 0;
    // this number is now unavailable in surrounding positions
    decrementSurrounding(i, j, c);
}

bool Technique::availableInRow(int* i0, char* c0) {
    for (int i=0; i<Board::N; i++) {
        for (char c='1'; c<='9'; c++) {
            if (countRow[i][Board::entryToIdx(c)] == 1) {
                *i0 = i;
                *c0 = c;
                text = "Open position in row " + std::to_string(i);
                return true;
            }
        }
    }
    return false;
}

bool Technique::availableInCol(int* j0, char* c0) {
    for (int j=0; j<Board::N; j++) {
        for (char c='1'; c<='9'; c++) {
            if (countCol[j][Board::entryToIdx(c)] == 1) {
                *j0 = j;
                *c0 = c;
                text = "Open position in col " + std::to_string(j);
                return true;
            }
        }
    }
    return false;
}

bool Technique::availableInSq(int* k0, char* c0) {
    for (int k=0; k<Board::N; k++) {
        for (char c='1'; c<='9'; c++) {
            if (countSq[k][Board::entryToIdx(c)] == 1) {
                *k0 = k;
                *c0 = c;
                text = "Open position in square " + std::to_string(k);
                return true;
            }
        }
    }
    return false;
}

bool Technique::oneAvailable(int* i0, int* j0) {
    for (int i=0; i<Board::N; i++) {
        for (int j=0; j<Board::N; j++) {
            if (countNums[i][j] == 1) {
                *i0 = i;
                *j0 = j;
                text = "Only entry available at (" + std::to_string(i) + ", " + std::to_string(j) + ")";
                return true;
            }
        }
    }
    return false;
}

bool Technique::nextAvailable(int* i0, int* j0, char* c0) {
    for (int i=0; i<Board::N; i++) {
        for (int j=0; j<Board::N; j++) {
            if (countNums[i][j] == 0) continue;

            for (char c='1'; c<='9'; c++) {
                if (isAvailable(i, j, c)) {
                    *i0 = i;
                    *j0 = j;
                    *c0 = c;
                    text = "Next available entry";
                    decrement(i, j, Board::entryToIdx(c));
                    return true;
                }
            }
        }
    }
    return false;
}
