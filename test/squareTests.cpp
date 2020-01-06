#include <catch.hpp>
#include "square.hpp"

TEST_CASE("square:loop", "[sudoku:square]") {
    Board b{};
    // loop over all squares k
    for (int k=0; k<Board::N; k++) {
        for (Square sq(k); sq.hasNext(); sq.next()) {
            int i, j;
            sq.getPos(&i, &j);

            int isq = b.getSquareNumber(i, j);
            char c = '0' + isq;
            if (c == '0') c = '9';
            b.insert(i, j, c);
            b.print();
        }
    }
}
