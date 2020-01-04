#!/bin/bash

#list default options

#g++ -o sudoku -std=c++17 -F /Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -I include src/*.cpp
#./sudoku

#testing option
#g++ -std=c++17 -I include -c test/allTests.cpp
g++ -std=c++17 -I include -o allTests allTests.o src/{square,board,technique,player,compPlayer}.cpp test/techniqueTests.cpp
./allTests
