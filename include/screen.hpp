//
//  screen.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//
//  Thank you Lazy Foo' Productions for SDL2 help

#ifndef screen_hpp
#define screen_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

struct Screen {
    const static int SCREEN_WIDTH = 700;   // screen width
    const static int SCREEN_HEIGHT = 650;  // screen height
    SDL_Window* window;                    // window
    SDL_Renderer* renderer;                // renderer
    TTF_Font* font;                        // text font

    /**
     * Initialize the screen
     * @param title title of screen
     * @param ffname font file path
     */
    Screen(const char* title, const char* ffname);

    /**
     * @return true if window, renderer, or font has stopped
     */
    bool notWorking() const;

    /**
     * close the screen
     */
    void close();
};

#endif /* screen_hpp */
