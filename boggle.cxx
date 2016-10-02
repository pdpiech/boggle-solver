/* Filename: boggle.cxx
 * Author: Peter Piech
 * Date Created: 07/29/2016
 * Date Modified: 08/01/2016
 * Description: Boggle game solver
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include "boggle.h"

// Constructor
Boggle::Boggle(const char* board_filename, const char* dict_filename) :
    m_solved(false), m_board(), m_dict(), m_solns() {
    init(board_filename, dict_filename); // defer to initialization helper
}

// Constructor
Boggle::Boggle(const std::string &board_filename, const std::string &dict_filename) :
    m_solved(false), m_board(), m_dict(), m_solns() {
    init(board_filename.c_str(), dict_filename.c_str()); // defer to initialization helper
}

// Output the game board
void Boggle::print_board() const {
    for (int i = 0; i < m_board_h; ++i) {
        std::cout << m_board[i] << std::endl;
    }
}

// Output all solutions
void Boggle::print_solutions() const {
    // move contents of hash set m_solns to a sortable container (e.g. vector)
    std::vector<std::string> solns_vec;
    solns_vec.assign(m_solns.begin(), m_solns.end());
    std::sort(solns_vec.begin(), solns_vec.end());

    // print out the solutions
    for (unsigned int i = 0; i < solns_vec.size(); ++i) {
        std::cout << solns_vec[i] << std::endl;
    }
}

// Analyze board & dictionary to find all solutions
void Boggle::solve() {

    // Init variables for recursive helper (they are copy constructed each call)
    bool* visited = new bool[m_board_h * m_board_w](); // init all to false
    std::string empty_str = std::string(); // initialize to empty string

    // for each board position, solve for words that begin at that position
    for (int i = 0; i < m_board_h; ++i) {
        for (int j = 0; j < m_board_w; ++j) {
            solve(visited, i, j, empty_str);
        }
    }

    m_solved = true; // board has been solved once loops complete
    delete[] visited; // deallocate dynamic memory
}

// Internal initialization helper for constructors
void Boggle::init(const char* board_filename, const char* dict_filename) {
    std::ifstream b_in(board_filename), d_in(dict_filename);
    if (!b_in.is_open()) {
        throw std::runtime_error(std::string("Failed to open: ") + board_filename);
    } else if (!d_in.is_open()) {
        throw std::runtime_error(std::string("Failed to open: ") + dict_filename);
    }
    bool first_line = true;
    std::string line;
    while (std::getline(b_in, line)) {
        if (first_line) {
            m_board_w = line.size(); // set width of board to width of row
            first_line = false;
        } else if (line.size() != (unsigned int)m_board_w) {
            throw std::runtime_error(std::string("Malformed board file: rows of differing length"));
        }
        m_board.push_back(line);
    }
    m_board_h = m_board.size(); // set height of board
    while (std::getline(d_in, line)) {
        m_dict.insert(line);
    }
}

// Internal index mapping 2D coordinates for for 1D array positions
int Boggle::index(const int row, const int col) const {
    return (row * m_board_w) + col; // return array index mapping from 2D indicies
}

// Internal boggle dictionary word checker
bool Boggle::isValidWord(const std::string &str) const {
    if (str.size() >= BOGGLE_MIN_VALID_WORD_LENGTH && m_dict.find(str) != m_dict.end()) {
        return true; // word is of proper length and in the dictionary
    }
    return false; // else
}

// Internal recursive solution finding helper function
void Boggle::solve(bool* const &visited, const int row, const int col, std::string &str) {
    visited[index(row, col)] = true; // visit the current position
    str += m_board[row][col]; // add current letter to string

    if (isValidWord(str)) { // check if str is a valid boggle word
        m_solns.insert(str); // add it to solutions if it is valid
    }

    // visit each of the (up to) eight neighboring positions recursively
    for (int i = row - 1; i <= row + 1 && i < m_board_h; ++i) {
        for (int j = col - 1; j <= col + 1 && j < m_board_w; ++j) {
            if (i >= 0 && j >= 0 && !visited[index(i, j)]) {
                solve(visited, i, j, str);
            }
        }
    }

    // reset string and visited before leaving this level of recursion
    str.erase(str.length() - 1); // remove current character from partial solution
    visited[index(row, col)] = false; // set current position as not visited
}
