#include <catch.hpp>
#include "compPlayer.hpp"
#include "dirent.h"

TEST_CASE("technique:tests", "[sudoku:technique]") {
    std::string dname = "technique_tests/";
    if (DIR* dir = opendir(dname.data())) {
        while (struct dirent* ent = readdir(dir)) {
            std::string fname = ent->d_name;

            if (fname.find(".txt") == std::string::npos) continue;
            CompPlayer p(fname, dname+fname, false, false, true);
            p.play();

            // what if wrong number inserted?
            REQUIRE(p.getNMoves() > 0);
        }
        closedir(dir);
    }

}
