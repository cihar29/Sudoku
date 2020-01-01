//
//  board.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/18/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <string>
#include <fstream>
#include "square.hpp"

class Board {
public :
    const static int N = 9;         // number of rows and columns in the board
    const static char BLANK = ' ';  // blank entry
private :
    int nFilled;                    // total filled entries
    int entries[N];                 // number of filled entries per entry
    char board[N][N];               // the board
    char board0[N][N];              // the initial board
    std::string text;               // current text

    /**
     * Set the text to t and print
     * @param t the new text
     * @param green true if text is green
     * @param red true if text is red
     */
    void setAndPrintText(std::string t, bool green = false, bool red = false);

    /**
     * Increment entry in the entries array
     * @param c the character entry to increment
     */
    void addEntry(char c);

    /**
     * Decrement entry in the entries array
     * @param c the character entry to decrement
     */
    void removeEntry(char c);

public :
    /**
     * Initialize empty board
     */
    Board();

    /**
     * Initialize board from file
     * @param fname the file name
     */
    Board(std::string fname);

    /**
     * Convert an entry c to an index
     * @param c the character entry
     * @return an index
     */
    static int entryToIdx(char c);

    /**
     * Get the square number of a row and col
     * @param i the row
     * @param j the col
     * @return the square number
     */
    static int getSquareNumber(int i, int j);

    /**
     * Initialize board0
     */
    void setInitialBoard();

    /**
     * Is this a valid Sudoku board?
     * @return true if valid
     */
    bool isValid();

    /**
     * Is this Sudoku board full?
     * @return true if full
     */
    bool isFull() const;

    /**
     * Get the number of entries for an entry in board
     * @param c the entry
     * @return the number of entries or -1 if c invalid
     */
    int nEntry(char c) const;

    /**
     * Is c in row i in board?
     * @param i the row
     * @param c the entry
     * @return true if c in row i
     */
    bool inRow(int i, char c) const;

    /**
     * Is c in col j in board?
     * @param j the col
     * @param c the entry
     * @return true if c in col j
     */
    bool inCol(int j, char c) const;

    /**
     * Is c in the square surrounding (i, j) in board?
     * @param i the row
     * @param j the col
     * @param c the entry
     * @return true if c in surrounding square
     */
    bool inSquare(int i, int j, char c) const;

    /**
     * Returns the entry at position (i, j) in board.
     * If position is invalid, return BLANK
     * @param i the row
     * @param j the column
     * @return entry at (i, j)
     */
    char at(int i, int j) const;

    /**
     * Is position (i, j) in board BLANK?
     * If position is invalid, return true
     * @param i the row
     * @param j the column
     * @return true if (i, j) is BLANK
     */
    bool isEmpty(int i, int j) const;

    /**
     * Insert entry into position (i, j) in board
     * @param i the row
     * @param j the column
     * @param c the entry to insert
     * @return true if number inserted
     */
    bool insert(int i, int j, char c);

    /**
     * Remove entry from position (i, j) in board
     * @param i the row
     * @param j the column
     * @return true if entry removed
     */
    bool remove(int i, int j);

    /**
     * Get the current board text
     * @return the board text
     */
    std::string getText() const;

    /**
     * Clear the board text
     */
    void clearText();

    /**
     * Print the board
     */
    void print() const;

    /**
     * Save board to a text file
     * @param fname the file name
     * @param title title displayed at the top of file
     * @param text text displayed at the bottom of file
     * @param subText subtext displayed below text
     */
    void save(std::string fname, std::string title = "", std::string text = "", std::string subText = "") const;
};

#endif /* board_hpp */
