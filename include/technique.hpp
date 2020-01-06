//
//  technique.hpp
//  Sudoku
//
//  Created by Charles Harrington on 12/26/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#ifndef technique_hpp
#define technique_hpp

#include <map>
#include <utility>
#include <vector>
#include "board.hpp"

class Technique {
    bool aNums[Board::N][Board::N][Board::N];   // true if an entry is available at a position on board
    int countNums[Board::N][Board::N];          // count number of available entries per position
    int countRow[Board::N][Board::N],           // available entry count per row
        countCol[Board::N][Board::N],           // available entry count per col
        countSq[Board::N][Board::N];            // available entry count per square
    std::string text;                           // text describing the technique
    typedef std::pair<int, int> pos;            // position (row, col) on board
    std::vector<std::pair<pos, char>> vBrute;   // list of available positions and numbers
    int iBrute;                                 // the current index in vBrute

    /**
     * Set the entries unavailable at position (i, j)
     * @param i the row
     * @param j the col
     * @param idx the index of the entry
     */
    void setUnavailablePos(int i, int j, int idx);

    /**
     * Set the entry c0 unavailable in the positions surrounding (i0, j0)
     * @param i0 the row
     * @param j0 the col
     * @param c0 the entry
     */
    void setUnavailableSurrounding(int i0, int j0, char c0);

    /**
     * Look for a phantom row (2 or 3 available entries in a row) in square k
     * @param k the square
     * @param c the entry
     * @param i0 the phantom row
     * @return true if phantom row found
     */
    bool phantomRowInSq(int k, char c, int* i0) const;

    /**
     * Look to set entries unavailable with a phantom row
     * @return true if phantom row causes entry to become unavailable
     */
    bool phantomRowSetUnavailable();

    /**
     * Look for a phantom col (2 or 3 available entries in a col) in square k
     * @param k the square
     * @param c the entry
     * @param j0 the phantom col
     * @return true if phantom col found
     */
    bool phantomColInSq(int k, char c, int* j0) const;

    /**
     * Look to set entries unavailable with a phantom col
     * @return true if phantom col causes entry to become unavailable
     */
    bool phantomColSetUnavailable();

    /**
     * Look for a phantom square (2 or 3 available entries in a square) in row i
     * @param i the row
     * @param c the entry
     * @param k0 the phantom square
     * @return true if phantom square found
     */
    bool phantomSqInRow(int i, char c, int* k0) const;

    /**
     * Look for a phantom square (2 or 3 available entries in a square) in col j
     * @param j the col
     * @param c the entry
     * @param k0 the phantom square
     * @return true if phantom square found
     */
    bool phantomSqInCol(int j, char c, int* k0) const;

    /**
     * Look to set entries unavailable with a phantom square
     * @param lookAtRow true if looking at phantomSqInRow, else look at phantomSqInCol
     * @return true if phantom square causes entry to become unavailable
     */
    bool phantomSqSetUnavailable(bool lookAtRow);

    /**
     * Look for entries with a pair of positions and match to other entries
     * @param entryPos the list of available positions per entry
     * @return true if clogging pair found and an available entry is made unavailable
     */
    bool matchPairs(const std::vector<pos>* entryPos);

    /**
     * Look for matching entries in pair of positions in a row
     * @return true if clogging pair found and an available entry is made unavailable
     */
    bool clogInRow();

    /**
     * Look for matching entries in pair of positions in a col
     * @return true if clogging pair found and an available entry is made unavailable
     */
    bool clogInCol();

    /**
     * Look for matching entries in pair of positions in a square
     * @return true if clogging pair found and an available entry is made unavailable
     */
    bool clogInSq();

public :
    /**
     * Initialize the techniques used to solve a Sodoku puzzle
     */
    Technique(const Board& b);

    /**
     * Is entry c available in board at (i, j)?
     * @param i the row
     * @param j the col
     * @param c the entry
     * @return true if c is available at (i, j) in board
     */
    bool isAvailable(int i, int j, char c) const;

    /**
     * Get the text describing the technique
     * @return the text describing the technique
     */
    std::string getText() const;

    /**
     * Modify available number arrays based on entry c inserted at (i, j)
     * @param i the row
     * @param j the col
     * @param c the entry
     */
    void insert(int i, int j, char c);

    /**
     * Check if any row has an entry available exactly once
     * @param i0 the available row
     * @param c0 the available entry
     * @return true if entry available once in a row
     */
    bool availableInRow(int* i0, char* c0);

    /**
     * Check if any col has an entry available exactly once
     * @param j0 the available col
     * @param c0 the available entry
     * @return true if entry available once in a col
     */
    bool availableInCol(int* j0, char* c0);

    /**
     * Check if any square has an entry available exactly once
     * @param k0 the available square
     * @param c0 the available entry
     * @return true if entry available once in a square
     */
    bool availableInSq(int* k0, char* c0);

    /**
     * Check if any position has only one available entry
     * @param i0 the available row
     * @param j0 the available col
     * @return true if a position has one available entry
     */
    bool oneAvailable(int* i0, int* j0);

    /**
     * Look for phantom rows or cols in the board
     * @return true if phantom found and an available entry is made unavailable
     */
    bool phantoms();

    /**
     * Look for pairs of entries that take up two positions in a row, col, or square
     * @return true if clogging pair found and an available entry is made unavailable
     */
    bool cloggingPairs();

    /**
     * Set up technique for brute force
     */
    void setBruteForce();

    /**
     * Get the next available entry c at position (i, j)
     * @param i the row
     * @param j the col
     * @param c the entry
     * @return true if an entry is available
     */
    bool getNextBrute(int* i, int* j, char* c);
};

#endif /* technique_hpp */
