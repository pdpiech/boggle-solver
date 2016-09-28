/* Filename: boggle_main.cxx
 * Author: Peter Piech
 * Date Created: 07/29/2016
 * Date Modified: 08/01/2016
 * Description: Boggle game solver
 */

#include "boggle.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

void print_usage(const char* argv0) {
    std::cout << "USAGE:\n\t" << argv0 << " <board file> <dictionary file> [-v|--verbose]";
    std::cout << std::endl;
    exit(0); // exit program
}

int main(int argc, char* argv[])
{
    bool verbose = false;
    if (argc < 3 || argc > 4) {
        std::cout << "Incorrect number of arguments given: " << argc << std::endl;
        print_usage(argv[0]); // print usage string and quit
    } else if (argc == 4) {
        verbose = true; // assume extra argument is good and check below

        // check if optional third argument is neither "-v" nor "--verbose"
        if (!(std::strcmp(argv[3], "-v") == 0) && !(std::strcmp(argv[3], "--verbose") == 0)) {
            std::cout << "Invalid argument: " << argv[3] << std::endl;
            print_usage(argv[0]); // print usage string and quit
        }
    }

    if (verbose) {
        std::cout << "Initializing boggle..." << std::endl;
    }
    Boggle game = Boggle(argv[1], argv[2]);
    if (verbose) {
        game.print_board();
        std::cout << "Solving boggle..." << std::endl;
    }
    game.solve();
    if (game.isSolved()) {
        game.print_solutions();
    } else {
        std::cerr << "ERROR: boggle board not solved" << std::endl;
    }
    return EXIT_SUCCESS;
}
