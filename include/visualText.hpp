//
//  visualText.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef visualText_hpp
#define visualText_hpp

#include <string>
#include "screen.hpp"
#include "board.hpp"

struct VisualText {
    char text;              // the text
    SDL_Texture* texture;   // text texture
    SDL_Rect rect1, rect2;  // rectangle for this texture and the target rectangle for the render

    /**
     * Default initialization
     */
    VisualText();

    /**
     * Initialize visual text from a char
     * @param s the screen
     * @param c text character
     * @param col color {R,G,B} where each component is between 0-255
     * @param p point on screen (x, y)
     * @param size text size
     * @param centerWidth the width to center the text on (set to -1 to disregard option)
     */
    VisualText(const Screen& s, char c, const SDL_Color& col, const SDL_Point& p, float size, int centerWidth = -1);

    /**
     * Initialize visual text from a string
     * @param s the screen
     * @param str text string
     * @param col color {R,G,B} where each component is between 0-255
     * @param p point on screen (x, y)
     * @param size text size
     * @param centerWidth the width to center the text on (set to -1 to disregard option)
     */
    VisualText(const Screen& s, std::string str, const SDL_Color& col, const SDL_Point& p, float size, int centerWidth = -1);

    /**
     * Is the text empty?
     * @return true if empty
     */
    bool isEmpty();

    /**
     * Clear the text and destroy the texture
     */
    void clear();
};

#endif /* visualText_hpp */
