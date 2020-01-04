# Sudoku
Interactive Sudoku game and step-by-step solver to demonstrate principles of OOP (inheritance, polymorphism, testing, etc)

**Contents**
[Start](#start)
[Instructions](#instructions)
[Gameplay](#gameplay)
[Testing](#testing)

# Start
1. Install [SDL2 framework](https://www.libsdl.org/download-2.0.php)
2. Get a font (.ttf file)
3. Run with `./run.sh` and you will find a few options
4. Fun options include
    1. `./run.sh -type cp`
    2. `./run.sh -type vp`
    3. `./run.sh -type vcp -walkthrough y`
    4. `./run.sh -type vcp -autosave y` (pretty pictures)
5. After you compile once, feel free to comment it out in `run.sh` 

# Instructions
1. Use `Player` class to play text-based
    1. `create` your own board
    2. Load a text file
2. Use `VisualPlayer` class to play visual version - this includes helping numbers!!!
    1. Press 'space' to add helping number
    2. Press 'a' to add all available helping numbers (very helpful for technique)
    3. Double-click a helping number to remove it
    4. Press 'c' to clear all helping numbers
3. Use `CompPlayer` class to solve a puzzle text-based (techniques are currently incomplete)
    1. Use `walkThrough` option to click through step-by-step solution
    2. `autoSave` option provides nice text file summary
4. `VisualCompPlayer` class to solve a puzzle visually
    1. Use `walkThrough` option to click through step-by-step solution
    2. `autoSave` option provides nice image summary

# Gameplay
<img src="save1/screenshot1.png" width="700"> 

Helping Numbers

<img src="save1/screenshot2.png" width="700">

# Testing
1. Get [Catch2](https://github.com/catchorg/Catch2) header file
