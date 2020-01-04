//
//  main.cpp
//  Sudoku
//
//  Created by Charles Harrington on 12/19/19.
//  Copyright © 2019 Charles Harrington. All rights reserved.
//

#include <map>
#include "visualCompPlayer.hpp"

bool str2Bool(std::string input) {
    return input == "y" || input == "yes" || input == "true";
}

int main(int argc, const char * argv[]) {

    // make save text better on visual board (not take over everything)
    // make sure all tests are passed in technique_test (add more technique methods)
    // add less hard puzzle to puzzles to demonstrate ease without brute force
    // tests - every method! (lots to test in technique)
    // make file with better compiler language

//    Player p("Chuck", std::string("puzzles/input1.txt"), false);
//    Player p("Chuck", true, false);
//    CompPlayer p("Chuck", std::string("puzzles/input1.txt"), true, false, false);
//    CompPlayer p("Chuck", true, false, true);
//    VisualPlayer p("Chuck", std::string("puzzles/input1.txt"), false);
//    VisualPlayer p("Chuck", true, false);
//    VisualCompPlayer p("Chuck", std::string("puzzles/input1.txt"), true, false);
//    VisualCompPlayer p("Chuck", true, false, true);

//    p.play();
//    return 0;

    std::map<std::string, std::string> mPars =
    {{"-type", ""}, {"-name", "Chuck"}, {"-file", "puzzles/input1.txt"},
     {"-create", "n"}, {"-autosave", "n"}, {"-walkthrough", "n"}};

    if (argc == 1) {
        printf("\nPlease provide some parameters:\n");
        printf("-type \t\tplayer (p), comp player (cp), visual player (vp), or visual comp player (vcp)\n");
        printf("-name \t\tname\n");
        printf("-file \t\tsudoku board text file\n");
        printf("-create \tcreate your own sudoku board (y/n)\n");
        printf("-autosave \tsave board after each move (y/n)\n");
        printf("-walkthrough \twork through puzzle step-by-step (y/n)\n");
        return -1;
    }
    else {
        // set the parameters
        for (int i=1; i<argc; i++) {
            std::string arg = argv[i];

            if (mPars.find(arg) != mPars.end()) {
                mPars[arg] = ""; // set to empty, not using the default option
                for (int i0=i; i+1<argc && argv[i+1][0] != '-'; i++)
                    mPars[arg] += (i==i0?"":" ") + (std::string)argv[i+1];
            }
            else printf("Unknown option: %s\n", arg.data());
        }
    }
    printf("\nParameters:\n");
    for (const auto& it : mPars) printf("%s\t%s\n", it.first.data(), it.second.data());
    printf("\n");

    std::string type        = mPars["-type"],
                name        = mPars["-name"],
                file        = mPars["-file"];
    bool        create      = str2Bool(mPars["-create"]),
                autosave    = str2Bool(mPars["-autosave"]),
                walkthrough = str2Bool(mPars["-walkthrough"]);
    Player* p = NULL;

    if (type == "p" || type == "player") {
        if (create)
            p = new Player(name, create, autosave);
        else
            p = new Player(name, file, autosave);
    }
    else if (type == "cp" || type == "comp player") {
        if (create)
            p = new CompPlayer(name, create, autosave, walkthrough);
        else
            p = new CompPlayer(name, file, autosave, walkthrough, false);
    }
    else if (type == "vp" || type == "visual player") {
        if (create)
            p = new VisualPlayer(name, create, autosave);
        else
            p = new VisualPlayer(name, file, autosave);
    }
    else if (type == "vcp" || type == "visual comp player") {
        if (create)
            p = new VisualCompPlayer(name, create, autosave, walkthrough);
        else
            p = new VisualCompPlayer(name, file, autosave, walkthrough);
    }
    else
        printf("Specify a known player '-type':\n"
               "player (p), comp player (cp), visual player (vp), or visual comp player (vcp)\n\n");

    if (p) {
        p->play();
        printf("Number of moves: %i\n\n", p->getNMoves());
        delete p;
    }
    return 0;
}
