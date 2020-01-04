#!/bin/bash

args=("$@")

if [ $# -eq 0 ] ; then

  echo
  echo "Please provide some parameters"
  echo "Example: ./run.sh -type cp -name Chuck -file puzzles/input1.txt"
  echo
  echo "Compiling..."

  g++ -o sudoku -std=c++17 -F /Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -I include src/*.cpp
  ./sudoku
  echo

elif [[ $# -eq 1 && ${args[0]} == "test" ]] ; then

  echo "Run tests"
  #g++ -std=c++17 -I include -c test/allTests.cpp
  #g++ -std=c++17 -I include -o allTests allTests.o src/{square,board,technique,player,compPlayer}.cpp test/techniqueTests.cpp
  #./allTests

else

  echo $*
  echo
  echo "Compiling..."

  g++ -o sudoku -std=c++17 -F /Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -I include src/*.cpp
  ./sudoku $*
  echo

fi
