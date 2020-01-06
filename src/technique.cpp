//
//  technique.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/26/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "technique.hpp"

Technique::Technique(const Board& b) : aNums{false}, countNums{0}, countRow{0}, countCol{0}, countSq{0}, iBrute(0) {

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

void Technique::setUnavailablePos(int i, int j, int idx) {
    aNums[i][j][idx] = false;
    countRow[i][idx]--;
    countCol[j][idx]--;
    countSq[Board::getSquareNumber(i, j)][idx]--;
    countNums[i][j]--;
}

void Technique::setUnavailableSurrounding(int i0, int j0, char c0) {
    int idx = Board::entryToIdx(c0);
    // check row i0
    for (int j=0; j<Board::N; j++)
        if (aNums[i0][j][idx])
            setUnavailablePos(i0, j, idx);

    // check col j0
    for (int i=0; i<Board::N; i++)
        if (aNums[i][j0][idx])
            setUnavailablePos(i, j0, idx);

    // check square surrounding (i0, j0)
    for (Square sq(i0, j0); sq.hasNext(); sq.next()) {
        int i, j;
        sq.getPos(&i, &j);
        if (aNums[i][j][idx])
            setUnavailablePos(i, j, idx);
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
            setUnavailablePos(i, j, idx);
    }
    // put this in test countNums[i][j] = 0;
    // this number is now unavailable in surrounding positions
    setUnavailableSurrounding(i, j, c);
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

bool Technique::phantomRowInSq(int k, char c, int* i0) const {
    bool phantom = false;
    *i0 = -1;
    for (Square sq(k); sq.hasNext(); sq.next()) {
        int i, j;
        sq.getPos(&i, &j);

        if (isAvailable(i, j, c)) {
            if (*i0 != -1 && *i0 != i)
                return false;
            *i0 = i;
            phantom = true;
        }
    }
    return phantom;
}

bool Technique::phantomRowSetUnavailable() {
    bool phantom = false;
    // look at all squares before returning
    for (int k=0; k<Board::N; k++) {
        for (char c='1'; c<='9'; c++) {

            if (int i; phantomRowInSq(k, c, &i)) {
                int idx = Board::entryToIdx(c);
                // set unavailable entries in same row but in different square
                for (int j=0; j<Board::N; j++) {
                    if (Board::getSquareNumber(i, j) == k) continue;
                    if (aNums[i][j][idx]) {
                        setUnavailablePos(i, j, idx);
                        printf("Phantom row: %c at (%i, %i) set unavailable\n\n", c, i, j);
                        phantom = true;
                    }
                }
            }
        }
    }
    return phantom;
}

bool Technique::phantomColInSq(int k, char c, int* j0) const {
    bool phantom = false;
    *j0 = -1;
    for (Square sq(k); sq.hasNext(); sq.next()) {
        int i, j;
        sq.getPos(&i, &j);

        if (isAvailable(i, j, c)) {
            if (*j0 != -1 && *j0 != j)
                return false;
            *j0 = j;
            phantom = true;
        }
    }
    return phantom;
}

bool Technique::phantomColSetUnavailable() {
    bool phantom = false;
    // look at all squares before returning
    for (int k=0; k<Board::N; k++) {
        for (char c='1'; c<='9'; c++) {

            if (int j; phantomColInSq(k, c, &j)) {
                int idx = Board::entryToIdx(c);
                // set unavailable entries in same col but in different square
                for (int i=0; i<Board::N; i++) {
                    if (Board::getSquareNumber(i, j) == k) continue;
                    if (aNums[i][j][idx]) {
                        setUnavailablePos(i, j, idx);
                        printf("Phantom col: %c at (%i, %i) set unavailable\n\n", c, i, j);
                        phantom = true;
                    }
                }
            }
        }
    }
    return phantom;
}

bool Technique::phantomSqInRow(int i, char c, int* k0) const {
    bool phantom = false;
    *k0 = -1;
    for (int j=0; j<Board::N; j++) {
        if (isAvailable(i, j, c)) {
            int k = Board::getSquareNumber(i, j);
            if (*k0 != -1 && *k0 != k)
                return false;
            *k0 = k;
            phantom = true;
        }
    }
    return phantom;
}

bool Technique::phantomSqInCol(int j, char c, int* k0) const {
    bool phantom = false;
    *k0 = -1;
    for (int i=0; i<Board::N; i++) {
        if (isAvailable(i, j, c)) {
            int k = Board::getSquareNumber(i, j);
            if (*k0 != -1 && *k0 != k)
                return false;
            *k0 = k;
            phantom = true;
        }
    }
    return phantom;
}

bool Technique::phantomSqSetUnavailable(bool lookAtRow) {
    bool phantom = false;
    // look at all rows or cols before returning
    for (int k=0; k<Board::N; k++) {
        for (char c='1'; c<='9'; c++) {

            int k0;
            bool phantomInSq = lookAtRow?phantomSqInRow(k, c, &k0):phantomSqInCol(k, c, &k0);
            if (phantomInSq) {
                int idx = Board::entryToIdx(c);
                // set unavailable entries in same square but in different row or col
                for (Square sq(k0); sq.hasNext(); sq.next()) {
                    int i, j;
                    sq.getPos(&i, &j);
                    if (lookAtRow) {
                        if (i == k) continue;
                    }
                    else {
                        if (j == k) continue;
                    }
                    if (aNums[i][j][idx]) {
                        setUnavailablePos(i, j, idx);
                        printf("Phantom sq: %c at (%i, %i) set unavailable\n\n", c, i, j);
                        phantom = true;
                    }
                }
            }
        }
    }
    return phantom;
}

bool Technique::phantoms() {
    bool phantom = false;
    // look at all rows, cols, and squares before returning
    if (phantomRowSetUnavailable())
        phantom = true;
    if (phantomColSetUnavailable())
        phantom = true;
    if (phantomSqSetUnavailable(true))
        phantom = true;
    if (phantomSqSetUnavailable(false))
        phantom = true;
    return phantom;
}

bool Technique::matchPairs(const std::vector<pos>* entryPos) {
    bool pairs = false;
    std::map<std::pair<pos, pos>, std::vector<char>> mPosPair;

    for (char c='1'; c<='9'; c++) {
        int idx = Board::entryToIdx(c);
        // check that entry has exactly two positions
        if (entryPos[idx].size() != 2) continue;
        mPosPair[std::make_pair(entryPos[idx][0], entryPos[idx][1])].push_back(c);
    }
    // get the clogging positions
    for (const auto& it : mPosPair) {
        const std::vector<char>& vEntries = it.second;
        if (vEntries.size() != 2) continue;

        // make other entries at clogging positions <pos1, pos2> unavailable
        pos pos1 = it.first.first, pos2 = it.first.second;
        char c1 = vEntries[0], c2 = vEntries[1];
        for (char c='1'; c<='9'; c++) {
            if (c == c1 || c == c2) continue;
            int idx = Board::entryToIdx(c);

            if (aNums[pos1.first][pos2.second][idx]) {
                setUnavailablePos(pos1.first, pos1.second, idx);
                printf("Clogging pairs: %c at (%i, %i) set unavailable\n\n", c, pos1.first, pos1.second);
                pairs = true;
            }
            if (aNums[pos2.first][pos2.second][idx]) {
                setUnavailablePos(pos2.first, pos2.second, idx);
                printf("Clogging pairs: %c at (%i, %i) set unavailable\n\n", c, pos2.first, pos2.second);
                pairs = true;
            }
        }
    }
    return pairs;
}

bool Technique::clogInRow() {
    bool clog = false;
    // look at all rows before returning
    for (int i=0; i<Board::N; i++) {
        // fill list of available positions per entry
        std::vector<pos> entryPos[Board::N];

        for (int idx=0; idx<Board::N; idx++)
            for (int j=0; j<Board::N; j++)
                if (aNums[i][j][idx])
                    entryPos[idx].push_back(std::make_pair(i, j));
        if (matchPairs(entryPos))
            clog = true;
    }
    return clog;
}

bool Technique::clogInCol() {
    bool clog = false;
    // look at all cols before returning
    for (int j=0; j<Board::N; j++) {
        // fill list of available positions per entry
        std::vector<pos> entryPos[Board::N];

        for (int idx=0; idx<Board::N; idx++)
            for (int i=0; i<Board::N; i++)
                if (aNums[i][j][idx])
                    entryPos[idx].push_back(std::make_pair(i, j));
        if (matchPairs(entryPos))
            clog = true;
    }
    return clog;
}

bool Technique::clogInSq() {
    bool clog = false;
    // look at all squares before returning
    for (int k=0; k<Board::N; k++) {
        // fill list of available positions per entry
        std::vector<pos> entryPos[Board::N];

        for (int idx=0; idx<Board::N; idx++) {
            for (Square sq(k); sq.hasNext(); sq.next()) {
                int i, j;
                sq.getPos(&i, &j);
                if (aNums[i][j][idx])
                    entryPos[idx].push_back(std::make_pair(i, j));
            }
        }
        if (matchPairs(entryPos))
            clog = true;
    }
    return clog;
}

bool Technique::cloggingPairs() {
    bool pairs = false;
    // look at all rows, cols, and squares before returning
    if (clogInRow())
        pairs = true;
    if (clogInCol())
        pairs = true;
    if (clogInSq())
        pairs = true;
    return pairs;
}

void Technique::setBruteForce() {
    for (int i=0; i<Board::N; i++) {
        for (int j=0; j<Board::N; j++) {
            if (countNums[i][j] == 0) continue;

            for (char c='1'; c<='9'; c++)
                if (isAvailable(i, j, c))
                    vBrute.push_back(std::make_pair(std::make_pair(i, j), c));
        }
    }
}

bool Technique::getNextBrute(int* i, int* j, char* c) {
    if (iBrute == vBrute.size())
        return false;
    else {
        pos p = vBrute[iBrute].first;
        *i = p.first;
        *j = p.second;
        *c = vBrute[iBrute].second;
        iBrute++;
        text = "Next available entry";
        return true;
    }
}
