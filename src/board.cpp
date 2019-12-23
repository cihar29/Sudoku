//
//  board.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/18/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include "board.hpp"

Board::Board() : nFilled(0), entries(), text("") {
    // set the board to BLANK
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            board[i][j] = BLANK;
    setInitialBoard();
}

void Board::setAndPrintText(std::string t, bool green, bool red) {
    text = t;

    // write text in color
    if      (green) t = "\n\033[32m" + t + "\033[0m\n\n";
    else if (red)   t = "\n\033[31m" + t + "\033[0m\n\n";

    printf("%s\n", t.data());
}

int Board::entryToIdx(char c) {
    return c - '0' - 1;
}

void Board::addEntry(char c) {
    int idx = entryToIdx(c);
    if (0<=idx && idx<N) {
        entries[idx]++;
        nFilled++;
    }
}

void Board::removeEntry(char c) {
    int idx = entryToIdx(c);
    if (0<=idx && idx<N && entries[idx]>0 && nFilled>0) {
        entries[idx]--;
        nFilled--;
    }
}

void Board::setInitialBoard() {
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            board0[i][j] = board[i][j];
}

Board::Board(std::string fname) : nFilled(0), entries(), text("") {
    std::ifstream file(fname);
    if (!file.is_open()) setAndPrintText(fname + " not found!");

    for (int i=0; i<N; i++) {
        if (std::string line; getline(file, line)) {

            size_t len = line.length();
            // ignore lines starting with #
            if (len > 0 && line[0] == '#') continue;
            else if (len > N) setAndPrintText("Too many characters");

            for (int j=0; j<N; j++) {
                if (j < len) {
                    char c = line[j];
                    if (49<=c && c<=57) {
                        board[i][j] = c;
                        addEntry(c);
                    }
                    // space or invalid character
                    else {
                        if (c != 32) setAndPrintText("Invalid character: " + std::string(1, c));
                        board[i][j] = BLANK;
                    }
                }
                // fill the rest of the columns
                else board[i][j] = BLANK;
            }
        }
        // fill the rest of the rows
        else {
            for (int j=0; j<N; j++) board[i][j] = BLANK;
        }
    }
    file.close();
    setInitialBoard();
}

bool Board::isValid() {
    // look at the kth row, col, and square for duplicate entries
    for (int k=0; k<N; k++) {
        bool dupRow[N] = {false}, dupCol[N] = {false}, dupSq[N] = {false};

        for (int j=0; j<N; j++) {
            char c = board[k][j];
            if (c == BLANK) continue;
            int idx = entryToIdx(c);
            if (dupRow[idx]) {
                setAndPrintText("Duplicate " + std::string(1, c) + " in row " + std::to_string(k));
                return false;
            }
            dupRow[idx] = true;
        }

        for (int i=0; i<N; i++) {
            char c = board[i][k];
            if (c == BLANK) continue;
            int idx = entryToIdx(c);
            if (dupCol[idx]) {
                setAndPrintText("Duplicate " + std::string(1, c) + " in col " + std::to_string(k));
                return false;
            }
            dupCol[idx] = true;
        }

        for (Square sq(k); sq.hasNext(); sq.next()) {
            int i, j;
            sq.getPos(&i, &j);
            char c = board[i][j];
            if (c == BLANK) continue;
            int idx = entryToIdx(c);
            if (dupSq[idx]) {
                setAndPrintText("Duplicate " + std::string(1, c) + " in sq " + std::to_string(k));
                return false;
            }
            dupSq[idx] = true;
        }
    }
    return true;
}

bool Board::isFull() const {
    return nFilled == N*N;
}

int Board::nEntry(char c) const {
    int idx = entryToIdx(c);
    if (0<=idx && idx<N) return entries[idx];
    else                 return -1;
}

bool Board::inRow(int i, char c) const {
    for (int j=0; j<N; j++) {
        if (board[i][j] == c) return true;
    }
    return false;
}

bool Board::inCol(int j, char c) const {
    for (int i=0; i<N; i++) {
        if (board[i][j] == c) return true;
    }
    return false;
}

bool Board::inSquare(int i, int j, char c) const {
    for (Square sq(i, j); sq.hasNext(); sq.next()) {
        int i0, j0;
        sq.getPos(&i0, &j0);
        if (board[i0][j0] == c) return true;
    }
    return false;
}

char Board::at(int i, int j) const {
    if (0<=i && i<N && 0<=j && j<N) return board[i][j];
    printf("Invalid position\n");
    return BLANK;
}

bool Board::isEmpty(int i, int j) const {
    return at(i, j) == BLANK;
}

bool Board::insert(int i, int j, char c) {
    if (0<=i && i<N && 0<=j && j<N) {
        if (board[i][j] == BLANK) {
            if (49<=c && c<=57) {
                board[i][j] = c;
                addEntry(c);
                setAndPrintText("Inserted " + std::string(1, c) + " at (" +
                                std::to_string(i) + ", " + std::to_string(j) + ")", true);
                return true;
            }
            else setAndPrintText("Invalid character to insert");
        }
        else setAndPrintText("Position is not empty: " + std::string(1, c) +
                             " at (" + std::to_string(i) + ", " + std::to_string(j) + ")" );
    }
    else setAndPrintText("Invalid position to insert");

    return false;
}

bool Board::remove(int i, int j) {
    if (0<=i && i<N && 0<=j && j<N) {
        if (board0[i][j] == BLANK) {
            char c = board[i][j];
            if (c != BLANK) {
                board[i][j] = BLANK;
                removeEntry(c);
                setAndPrintText("Removed " + std::string(1, c) + " from (" +
                                std::to_string(i) + ", " + std::to_string(j) + ")", false, true);
                return true;
            }
            else setAndPrintText("Position is empty");
        }
        else setAndPrintText("Cannot remove an original number");
    }
    else setAndPrintText("Invalid position to remove");

    return false;
}

std::string Board::getText() const {
    return text;
}

void Board::clearText() {
    text = "";
}

void Board::print() const {
    std::string s = "";
    for (int i=0; i<N; i++) {
        if (i!=0 && i%3 == 0)
            s += "---------------------\n";

        for (int j=0; j<N; j++) {
            if (j!=0 && j%3 == 0)
                s += "| ";
            s += std::string(1, board[i][j]) + " ";
        }
        s += "\n";
    }
    printf("%s\n", s.data());
}

void Board::save(std::string fname, std::string title, std::string text, std::string subText) const {

    std::ofstream file(fname.data());
    if (!title.empty()) file << "### " << title << " ###" << std::endl;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) file << board[i][j];
        file << "\n";
    }
    if (!text.empty())    file << "### " << text << " ###" << std::endl;
    if (!subText.empty()) file << "### " << subText << " ###" << std::endl;
    file.close();

    printf("Board saved to %s\n\n", fname.data());
}
