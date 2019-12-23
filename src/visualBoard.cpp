//
//  visualBoard.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "visualBoard.hpp"

void VisualBoard::setTitle(std::string t) {
    title.clear();
    title = VisualText(s, t, BLACK, {BXPOS, BOARD_HEIGHT/24}, 0.5, BOARD_WIDTH);
}

void VisualBoard::fillBoard(const Board& b) {
    // clear old outlines
    for (int i=0; i<Board::N; i++) vOutlinePos[i].clear();

    for (int i=0; i<Board::N; i++) {
        for (int j=0; j<Board::N; j++) {
            nums[i][j].clear();

            SDL_Point pos = board2Screen(i, j);
            char c = b.at(i, j);
            // create text at pos representing entry on sudoku board
            nums[i][j] = VisualText(s, c, BLACK, pos, 1, BOARD_WIDTH/Board::N);

            // set outline positions for each entry
            if (c != Board::BLANK)
                vOutlinePos[b.entryToIdx(c)].push_back(pos);
        }
    }
}

VisualBoard::VisualBoard(const Board& b, std::string t) :
Visual(), s("Sudoku", FONT), rPos(OFFSCREEN), gPos(OFFSCREEN), helpers(BLUE, RED, 0.33) {

    if (s.notWorking()) return;
    setTitle(t);

    // set the lines
    for (int i=0; i<NLINES/2; i++) {
        int lwidth = 2;
        if (i%(int)sqrt(Board::N) == 0) lwidth = 5;

        lines[i] = {BXPOS+i*BOARD_WIDTH/Board::N, BYPOS, lwidth, BOARD_HEIGHT};
        lines[NLINES/2+i] = {BXPOS, BYPOS+i*BOARD_HEIGHT/Board::N, BOARD_WIDTH, lwidth};
    }
    fillBoard(b);
    render();
}

void VisualBoard::setText(std::string t1, std::string t2) {
    if (!t1.empty()) {
        text.clear();
        text = VisualText(s, t1, BLACK, {BXPOS, BYPOS+21*BOARD_HEIGHT/20}, 0.5, BOARD_WIDTH);
    }
    if (!t2.empty()) {
        subText.clear();
        subText = VisualText(s, t2, BLACK, {BXPOS, BYPOS+10*BOARD_HEIGHT/9}, 0.5, BOARD_WIDTH);
    }
}

bool VisualBoard::insert(Board* b) {
    if (s.notWorking()) return false;
    // get rPos in board coordinates (i, j)
    int i, j;
    screen2Board(rPos, &i, &j);

    // check with the actual board
    char c = rNum.text;
    if (b->insert(i, j, c)) {

        nums[i][j] = VisualText(s, c, GOLD, rPos, 1, BOARD_WIDTH/Board::N);
        rNum.clear();
        vOutlinePos[b->entryToIdx(c)].push_back(rPos);
/*
        ////////////put this in separate method!!!!!!!!!!!!!
        //remove helping numbers at position (i, j)
        for ( VisualChar& vc : smallNums[i][j] ) {
            //remove outlines
            std::vector<SDL_Point>& v = m_outlineSmallPos[ vc.vChar ];
            for (auto it = v.begin(); it != v.end(); ++it) {
                if ( it->x == vc.rect2.x && it->y == vc.rect2.y ) { it = v.erase( it ); it--; }
            }
            //remove small numbers
            vc.clear();
        }
        smallNums[i][j].clear();

        //////////////use separate method!!!!!!!!!
        //remove helping numbers in same row, col, or square
        std::vector<SDL_Point>& v = m_outlineSmallPos[ vNums[i][j].vChar ];
        for (auto it = v.begin(); it != v.end(); ++it) {
            int small_i, small_j;
            cartesian2Board( *it, &small_i, &small_j );

            // if same row, col, or square, then remove
            if ( small_i==i || small_j==j || Square::pos2Square( {i,j} )==Square::pos2Square( {small_i,small_j} ) ) {
                //remove outline
                it = v.erase( it ); //since not breaking, must recalculate v.end()
                it--;

                std::vector<VisualChar>& v2 = smallNums[ small_i ][ small_j ];
                for (auto it2 = v2.begin(), end_it2 = v2.end(); it2 != end_it2; ++it2) {

                    if ( it2->vChar == vNums[i][j].vChar ) {
                        //remove small number
                        it2->clear();
                        v2.erase( it2 );
                        rearrangeSmallNums( small_i, small_j, it2, s );
                        break;
                    }
                }
            }
        }*/
        return true;
    }
    else return false;
}

bool VisualBoard::remove(Board* b) {
    // get rPos in board coordinates (i, j)
    int i, j;
    screen2Board(rPos, &i, &j);

    // check with the actual board
    if (b->remove(i, j)) {
        int idx = b->entryToIdx(nums[i][j].text);
        nums[i][j].clear();

        // remove outline position
        std::vector<SDL_Point>& v = vOutlinePos[idx];
        for (auto it = v.begin(), end_it = v.end(); it != end_it; ++it) {

            if (it->x==rPos.x && it->y==rPos.y) {
                v.erase(it);
                break;
            }
        }
        return true;
    }
    else return false;
}

bool VisualBoard::rPosMovement(const SDL_Event& e) {
    int i, j;
    screen2Board(rPos, &i, &j);

    switch(e.key.keysym.sym) {
        case SDLK_UP:
            // take care going from 0 -> 8
            rPos.y = BYPOS + ((i==0?Board::N:i)-1) * BOARD_HEIGHT/Board::N;
            return true;
        case SDLK_DOWN:
            rPos.y = BYPOS + (i+1)%Board::N * BOARD_HEIGHT/Board::N;
            return true;
        case SDLK_LEFT:
            // take care going from 0 -> 8
            rPos.x = BXPOS + ((j==0?Board::N:j)-1) * BOARD_WIDTH/Board::N;
            return true;
        case SDLK_RIGHT:
            rPos.x = BXPOS + (j+1)%Board::N * BOARD_WIDTH/Board::N;
            return true;
        case SDLK_ESCAPE:
            rPos = OFFSCREEN;
            return true;
    }
    return false;
}

bool VisualBoard::isOnscreen(const SDL_Point& p) const {
    return p.x > OFFSCREEN.x;
}

void VisualBoard::handleEvent(const SDL_Event& e) {
    if (s.notWorking()) return;

    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        // draw green outline if mouse inside board
        if (BXPOS<x && x<BXPOS+BOARD_WIDTH && BYPOS<y && y<BYPOS+BOARD_HEIGHT) {

            // round (x, y) to nearest square outline
            gPos.x = BXPOS + (x-BXPOS)*Board::N/BOARD_WIDTH*BOARD_WIDTH/Board::N;
            gPos.y = BYPOS + (y-BYPOS)*Board::N/BOARD_HEIGHT*BOARD_HEIGHT/Board::N;

            // mouse click to draw red outline
            if (e.type == SDL_MOUSEBUTTONUP) {
                rPos = gPos;
                rNum.clear();
            }
        }
        else gPos = OFFSCREEN;
    }
    else if (e.type == SDL_KEYDOWN && isOnscreen(rPos)) {
        if (rPosMovement(e))
            rNum.clear();
        else {
            // make new number if number key is pressed and position on board is empty
            SDL_Keycode c = e.key.keysym.sym;
            if (SDLK_1<=c && c<=SDLK_9) {
                int i, j;
                screen2Board(rPos, &i, &j);
                if (nums[i][j].isEmpty()) {
                    rNum.clear();
                    rNum = VisualText(s, c, GREEN, rPos, 1, BOARD_WIDTH/Board::N);
                }
            }
        }
    }
}

bool VisualBoard::handleHelpers(const Board& b, const SDL_Event& e) {
    if (s.notWorking()) return false;

    // double click removes a helping number
    if (e.type == SDL_MOUSEBUTTONUP && e.button.clicks == 2) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        helpers.remove({x, y}, s);
    }
    // use 'space', 'a', and 'c' to add single, add all, or clear all helpers
    else if (e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
            case SDLK_SPACE: {
                std::string err = "";
                if (helpers.add(rPos, rNum.text, b, s, &err))
                    rNum.clear();
                else if (!err.empty()) {
                    setText(err);
                    return true;
                }
                break;
            }
            case SDLK_a:
                helpers.addAll(b, s);
                break;
            case SDLK_c:
                helpers.clear();
                break;
        }
    }
    return false;
}

void VisualBoard::render() {
    if (s.notWorking()) return;
    SDL_SetRenderDrawColor(s.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // clear screen
    SDL_RenderClear(s.renderer);

    // draw lines
    SDL_SetRenderDrawColor(s.renderer, 0x00, 0x00, 0x00, 0xFF);
    for (int i=0; i<NLINES; i++) SDL_RenderFillRect(s.renderer, &lines[i]);

    // draw board numbers
    for (int i=0; i<Board::N; i++)
        for (int j=0; j<Board::N; j++)
            SDL_RenderCopy(s.renderer, nums[i][j].texture, &nums[i][j].rect1, &nums[i][j].rect2);

    // draw helping numbers
    helpers.renderNums(s);

    // if gpos is on the visual board
    if (isOnscreen(gPos))
        drawOutline(s, GREEN, gPos);

    // if rpos is on the visual board
    if (isOnscreen(rPos)) {
        drawOutline(s, RED, rPos);

        // draw current pressed number
        SDL_RenderCopy(s.renderer, rNum.texture, &rNum.rect1, &rNum.rect2);

        // get the new entry we have pressed or old entry currently highlighted
        char c = rNum.text;
        if (rNum.isEmpty()) {
            int i, j;
            screen2Board(rPos, &i, &j);
            c = nums[i][j].text;
        }
        if (c != Board::BLANK) {
            int idx = Board::entryToIdx(c);
            // draw outlined numbers
            for (SDL_Point const& pos : vOutlinePos[idx])
                drawOutline(s, RED, pos);

            // draw outlined helping numbers
            helpers.renderOutlines(s, idx);
        }
    }
    // draw title
    SDL_RenderCopy(s.renderer, title.texture, &title.rect1, &title.rect2);

    // draw text
    SDL_RenderCopy(s.renderer, text.texture, &text.rect1, &text.rect2);

    // draw subtext
    SDL_RenderCopy(s.renderer, subText.texture, &subText.rect1, &subText.rect2);

    // update screen
    SDL_RenderPresent(s.renderer);
}

void VisualBoard::save(std::string fname) {
    SDL_Surface* screenshot = SDL_CreateRGBSurface(0, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, 32,
                                                   0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(s.renderer, NULL, SDL_GetWindowPixelFormat(s.window), screenshot->pixels, screenshot->pitch);
    IMG_SavePNG(screenshot, fname.data());
    SDL_FreeSurface(screenshot);

    setText("Visual Board saved to " + fname);
    render();
}

void VisualBoard::clear() {
    rNum.clear();
    text.clear();
    subText.clear();
    title.clear();
    helpers.clear();

    for (int i=0; i<Board::N; i++) {
        vOutlinePos[i].clear();
        for (int j=0; j<Board::N; j++)
            nums[i][j].clear();
    }
    s.close();
}
