//
//  visualText.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "visualText.hpp"

VisualText::VisualText() : text(Board::BLANK), texture(NULL) {

}

VisualText::VisualText(const Screen& s, char c, const SDL_Color& col, const SDL_Point& p,
                       float size, int centerWidth) : text(c), texture(NULL) {

    SDL_Surface* surface = TTF_RenderGlyph_Solid(s.font, c, col);
    texture = SDL_CreateTextureFromSurface(s.renderer, surface);
    rect1 = {0, 0, surface->w, surface->h};

    int x = p.x;
    if (centerWidth != -1)
        x += (centerWidth - int(size*surface->w)) / 2;
    rect2 = {x, p.y, int(size * surface->w), int(size * surface->h)};
    SDL_FreeSurface(surface);
}

VisualText::VisualText(const Screen& s, std::string str, const SDL_Color& col, const SDL_Point& p,
                       float size, int centerWidth) : text(' '), texture(NULL) {

    SDL_Surface* surface = TTF_RenderText_Solid(s.font, str.empty()?" ":str.data(), col);
    texture = SDL_CreateTextureFromSurface(s.renderer, surface);
    rect1 = {0, 0, surface->w, surface->h};

    float len = str.length();
    if      (len > 75) size *= len/150;
    else if (len > 55) size *= len/75;

    int x = p.x;
    if (centerWidth != -1)
        x += (centerWidth - int(size*surface->w)) / 2;
    rect2 = {x, p.y, int(size*surface->w), int(size*surface->h)};
    SDL_FreeSurface(surface);
}

bool VisualText::isEmpty() {
    return text == Board::BLANK;
}

void VisualText::clear() {
    text = Board::BLANK;
    SDL_DestroyTexture(texture);
    texture = NULL;
}
