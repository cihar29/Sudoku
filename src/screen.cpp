//
//  screen.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//
//  Thank you Lazy Foo' Productions for SDL2 help

#include "screen.hpp"

Screen::Screen(const char* title, const char* ffname) : window(NULL), renderer(NULL), font(NULL) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {

        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            printf("Warning: Linear texture filtering not enabled!\n");

        // Create window
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window != NULL) {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer != NULL) {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize SDL_ttf
                if (TTF_Init() != -1) {
                    // Open the font
                    font = TTF_OpenFont(ffname, 50);

                    if (font == NULL) printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
                }
                else printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            }
            else printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
    else printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
}

bool Screen::notWorking() const {
    return window==NULL || renderer==NULL || font==NULL;
}

void Screen::close() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    font = NULL;
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
