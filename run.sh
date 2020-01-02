#!/bin/bash

g++ -o sudoku -std=c++17 -F /Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -I include src/*.cpp
./sudoku
