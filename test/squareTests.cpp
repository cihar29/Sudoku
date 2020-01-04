#include <catch.hpp>
#include "square.hpp"

TEST_CASE("square:tests", "[sudoku:square]") {
    // print the square number using getSquareNumber for each position in square

    //////put these tests somewhere
    for (int i=0; i<Board::N; i++) {
        for (int j=0; j<Board::N; j++) {
            Square s(i, j);
            int i0, j0;
            s.getPos(&i0, &j0);
            printf("(%i, %i) starts at (%i, %i)\n", i, j, i0, j0);
        }
    }
}

TEST_CASE("square:tests", "[sudoku:square]") {
    Board b{};
    for (int k=0; k<Board::N; k++) {
        char c = '1';
        for (Square sq(k); sq.hasNext(); sq.next()) {
            int i, j;
            sq.getPos(&i, &j);
            b.insert(i, j, c);
            b.print();
            b.save("test.txt");
            c++;
        }
    }
}
