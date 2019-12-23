//
//  visual.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/22/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "visual.hpp"

Visual::Visual() {
    
}

SDL_Point Visual::board2Screen(int i, int j) const {
    return {BXPOS + j*BOARD_WIDTH/Board::N, BYPOS + i*BOARD_HEIGHT/Board::N};
}

void Visual::screen2Board(const SDL_Point& pos, int* i, int* j) const {
    *i = float(pos.y-BYPOS) * Board::N / BOARD_HEIGHT + 0.02;
    *j = float(pos.x-BXPOS) * Board::N / BOARD_WIDTH + 0.02;
}

void Visual::drawOutline(const Screen& s, const SDL_Color& col, const SDL_Point& pos, int scale, float xoff) {
    SDL_Rect rect[4];
    int x = pos.x - xoff;

    rect[0] = {x, pos.y, 3, BOARD_HEIGHT/Board::N/scale};
    rect[1] = {x, pos.y, BOARD_WIDTH/Board::N/scale, 3};
    rect[2] = {x+BOARD_WIDTH/Board::N/scale, pos.y, 3, BOARD_HEIGHT/Board::N/scale};
    rect[3] = {x, pos.y+BOARD_HEIGHT/Board::N/scale, BOARD_WIDTH/Board::N/scale, 3};

    SDL_SetRenderDrawColor(s.renderer, col.r, col.g, col.b, 0xFF);
    for (int i=0; i<4; i++) SDL_RenderFillRect(s.renderer, &rect[i]);
}
