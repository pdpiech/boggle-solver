/* Filename: boggle.h
 * Author: Peter Piech
 * Date Created: 07/29/2016
 * Date Modified: 08/01/2016
 * Description: Boggle game solver
 */

#ifndef BOGGLE_20160729_H_
#define BOGGLE_20160729_H_

#include <string>
#include <vector>
#include <tr1/unordered_set>

// Minimum length of valid words from official Boggle game rules
const static unsigned int BOGGLE_MIN_VALID_WORD_LENGTH = 3;

// Boggle class represents an instance of the game of boggle
class Boggle {
private:
    // Typedefs
    typedef std::tr1::unordered_set<std::string> words_set; // boggle internal set type

    // Member variables
    bool m_solved; // Indicates if solve method completed successfully
    int m_board_h, m_board_w; // Board height & width
    std::vector<std::string> m_board; // Vector entries are rows of the board
    words_set m_dict, m_solns; // Dictionary & solutions sets

    // Helper functions
    void init(const char* board_filename, const char* dict_filename);
    int index(const int row, const int col) const;
    bool isValidWord(const std::string &str) const;
    void solve(bool* const &visited, const int row, const int col, std::string &str);

public:
    // Constructor
    Boggle(const char* board_filename, const char* dict_filename);
    Boggle(const std::string &board_filename, const std::string &dict_filename);

    // Accessors
    bool isSolved() const { return m_solved; } // Return state of the game
    void print_board() const; // Output the game board
    void print_solutions() const; // Output all solutions

    // Modifiers
    void solve(); // Analyze board & dictionary to find all solutions
};

#endif /* BOGGLE_20160729_H_ */
