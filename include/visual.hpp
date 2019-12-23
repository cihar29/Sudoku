//
//  visual.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/22/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef visual_hpp
#define visual_hpp

#include "screen.hpp"
#include "board.hpp"

class Visual {
protected :
    const int BOARD_WIDTH = 500;                    // board width
    const int BOARD_HEIGHT = 500;                   // board height
    const int BXPOS =
        (Screen::SCREEN_WIDTH - BOARD_WIDTH)/2;     // left start position of board
    const int BYPOS =
        (Screen::SCREEN_HEIGHT - BOARD_HEIGHT)/3;   // top start position of board
    const SDL_Point OFFSCREEN = {-1, -1};           // position where point is off the screen
    const char* FONT = "Trebuchet MS Bold.ttf";     // text font on screen
    const SDL_Color BLACK = {0,0,0};                // color black
    const SDL_Color RED = {255,0,0};                // color red
    const SDL_Color GREEN = {0,255,0};              // color green
    const SDL_Color BLUE = {0,0,255};               // color blue
    const SDL_Color GOLD = {204,204,0};             // color gold

    /**
     * Initialize visual
     */
    Visual();

    /**
     * Convert board coordinates (i, j) to screen coordinates (x, y)
     * @param i row
     * @param j col
     * @return the screen coordinates (x, y)
     */
    SDL_Point board2Screen(int i, int j) const;

    /**
     * Convert screen coordinates (x, y) to board coordinates (i, j)
     * @param pos screen position
     * @param i row
     * @param j col
     */
    void screen2Board(const SDL_Point& pos, int* i, int* j) const;

    /**
     * Draw a rectangular outline at position pos on screen
     * @param s the screen
     * @param col the color
     * @param pos the position
     * @param scale scale is normalized to size of an entry on board
     * @param xoff the x offset
     */
    void drawOutline(const Screen& s, const SDL_Color& col, const SDL_Point& pos, int scale = 1, float xoff = 0);

    /**
     * Clear the objects
     */
    virtual void clear() = 0;
};

#endif /* visual_hpp */
