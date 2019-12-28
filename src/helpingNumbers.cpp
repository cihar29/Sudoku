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

SDL_Point helpingNumbers::getPos(const SDL_Point& pos, int idx) const {
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

    SDL_Point helpingPos = getPos(pos, vNums[i][j].size());
    vNums[i][j].push_back(VisualText(s, c, COLOR, helpingPos, SIZE));
    vOutlinePos[b.entryToIdx(c)].push_back(helpingPos);
    return true;
}

void helpingNumbers::rearrangeNums(const SDL_Point& pos, std::vector<VisualText>& v,
                                   std::vector<VisualText>::iterator it, const Screen& s) {
    for (auto end_it = v.end(); it != end_it; ++it) {

        char c = it->text;
        SDL_Point oldPos = {it->rect2.x, it->rect2.y};
        int idx = it - v.begin();
        SDL_Point newPos = getPos(pos, idx);

        it->clear();
        // shift number back a position (all other attributes remain the same)
        *it = VisualText(s, c, COLOR, newPos, SIZE);

        // shift the outline from oldPos to newPos
        std::vector<SDL_Point>& v2 = vOutlinePos[Board::entryToIdx(it->text)];
        for (auto it2 = v2.begin(), end_it2 = v2.end(); it2 != end_it2; ++it2) {

            if (it2->x == oldPos.x && it2->y == oldPos.y) {
                *it2 = newPos;
                break;
            }
        }
    }
}

void helpingNumbers::remove(const SDL_Point& pos, const Screen& s) {
    int i, j;
    screen2Board(pos, &i, &j);

    // list of helping numbers at (i, j) on board
    std::vector<VisualText>& v = vNums[i][j];
    for (auto it = v.begin(), end_it = v.end(); it != end_it; ++it) {

        // mouse click is within rectangle of helping number
        if (it->rect2.x <= pos.x && pos.x < it->rect2.x+it->rect2.w &&
            it->rect2.y <= pos.y && pos.y < it->rect2.y+it->rect2.h) {

            // list of outlines for helping number it->text
            std::vector<SDL_Point>& v2 = vOutlinePos[Board::entryToIdx(it->text)];
            for (auto it2 = v2.begin(), end_it2 = v2.end(); it2 != end_it2; ++it2) {

                // remove outline
                if (it2->x == it->rect2.x && it2->y == it->rect2.y) {
                    v2.erase(it2);
                    break;
                }
            }
            // remove number
            it->clear();
            v.erase(it);
            rearrangeNums(board2Screen(i, j), v, it, s);
            break;
        }
    }
}

// opposite approach compared to remove method above
// here we start with outline loop, and then enter number loop
void helpingNumbers::removeSurrounding(int i, int j, char c, const Screen& s) {
    if (c == Board::BLANK) return;

    // look for helping numbers in the same row, col, or square as c with the same value
    std::vector<SDL_Point>& v = vOutlinePos[Board::entryToIdx(c)];
    for (auto it = v.begin(); it != v.end(); ++it) {

        int i0, j0;
        screen2Board(*it, &i0, &j0);

        if (i0 == i || j0 == j || Board::getSquareNumber(i0, j0) == Board::getSquareNumber(i, j)) {
            // remove outline
            it = v.erase(it); // since we keep looping, we must recalculate v.end()
            it--;

            std::vector<VisualText>& v2 = vNums[i0][j0];
            for (auto it2 = v2.begin(), end_it2 = v2.end(); it2 != end_it2; ++it2) {

                if (it2->text == c) {
                    // remove number
                    it2->clear();
                    v2.erase(it2);
                    rearrangeNums(board2Screen(i0, j0), v2, it2, s);
                    break;
                }
            }
        }
    }
}

void helpingNumbers::removeAllAt(int i, int j) {
    // for all helping numbers at (i, j)
    for (VisualText& num : vNums[i][j]) {

        // remove outline
        std::vector<SDL_Point>& v = vOutlinePos[Board::entryToIdx(num.text)];
        for (auto it = v.begin(); it != v.end(); ++it) {

            if (it->x == num.rect2.x && it->y == num.rect2.y ) {
                it = v.erase(it);
                it--;
            }
        }
        // remove number
        num.clear();
    }
    vNums[i][j].clear();
}

void helpingNumbers::addAll(const Board& b, const Screen& s) {
    clear();
    Technique t(b);

    for (int i=0; i<Board::N; i++) {
        for (int j=0; j<Board::N; j++) {
            if (b.at(i, j) != Board::BLANK) continue;

            // look at available entries in board
            for (char c='1'; c<='9'; c++) {
                if (t.isAvailable(i, j, c)) {
                    SDL_Point pos = getPos(board2Screen(i, j), vNums[i][j].size());
                    vNums[i][j].push_back(VisualText(s, c, COLOR, pos, SIZE));
                    vOutlinePos[b.entryToIdx(c)].push_back(pos);
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
