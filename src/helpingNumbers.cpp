//
//  helpingNumbers.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/21/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "helpingNumbers.hpp"

helpingNumbers::helpingNumbers(const SDL_Color& c, const SDL_Color& lineColor, float s) :
Visual(), COLOR(c), LINECOLOR(lineColor), SIZE(s), SRN(sqrt(Board::N)) {
    
}

SDL_Point helpingNumbers::getPos(const SDL_Point& pos, int i, int j) const {
    int idx = vNums[i][j].size();

    int x = pos.x + (float)BOARD_WIDTH/Board::N * (1.0/9 + float(idx%SRN)/SRN);
    int y = pos.y + (float)BOARD_HEIGHT/Board::N * (1.0/12 + float(idx/SRN)/SRN);
    return {x, y};
}

bool helpingNumbers::add(const SDL_Point& pos, char c, const Board& b, const Screen& s, std::string* text) {
    if (c == Board::BLANK) return false;

    int i, j;
    screen2Board(pos, &i, &j);

    // check if c already exists in collection
    for (const VisualText& num : vNums[i][j]) {
        if (num.text == c) return false;
    }
    // check if c is in row, col, or square
    if (b.inRow(i, c)) {
        *text = "Invalid helper: " + std::string(1, c) + " in row";
        return false;
    }
    else if (b.inCol(j, c)) {
        *text = "Invalid helper: " + std::string(1, c) + " in column";
        return false;
    }
    else if (b.inSquare(i, j, c)) {
        *text = "Invalid helper: " + std::string(1, c) + " in square";
        return false;
    }

    SDL_Point helpingPos = getPos(pos, i, j);
    vNums[i][j].push_back(VisualText(s, c, COLOR, helpingPos, SIZE));
    vOutlinePos[b.entryToIdx(c)].push_back(helpingPos);
    return true;
}

void helpingNumbers::remove(const SDL_Point& pos, const Screen& s) {

}

void helpingNumbers::addAll(const Board& b, const Screen& s) {
    clear();

    // mark entries in each row, col, and square
    bool rows[Board::N][Board::N], cols[Board::N][Board::N], sqs[Board::N][Board::N];
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
            for (char c='1'; c<='9'; c++) {
                int idx = b.entryToIdx(c);
                if (!rows[i][idx] && !cols[j][idx] && !sqs[k][idx]) {

                    SDL_Point pos = getPos(board2Screen(i, j), i, j);
                    vNums[i][j].push_back(VisualText(s, c, COLOR, pos, SIZE));
                    vOutlinePos[idx].push_back(pos);
                }
            }
        }
    }
}

void helpingNumbers::renderNums(const Screen& s) {
    for (int i=0; i<Board::N; i++)
        for (int j=0; j<Board::N; j++)
            for (const VisualText& num : vNums[i][j])
                SDL_RenderCopy(s.renderer, num.texture, &num.rect1, &num.rect2);
}

void helpingNumbers::renderOutlines(const Screen& s, int idx) {
    if (idx < 0 || idx >= Board::N) return;

    for (const SDL_Point& pos : vOutlinePos[idx])
        drawOutline(s, LINECOLOR, pos, 3, BOARD_WIDTH/Board::N/9.0);
}

void helpingNumbers::clear() {
    for (int i=0; i<Board::N; i++) {
        vOutlinePos[i].clear();

        for (int j=0; j<Board::N; j++) {
            for (VisualText& num : vNums[i][j])
                num.clear();
            vNums[i][j].clear();
        }
    }
}
