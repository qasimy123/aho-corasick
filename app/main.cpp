#include "aho-corasick.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#define PROMPT "Enter text to search or 's' to search Shrek 3"
/*
 * Simple main program that demontrates the usage of the Aho-Corasick on
 * the full script of Shrek 3. Src: https://github.com/mackenziedg/shrek/blob/master/data/shrek3.txt
 */
int main()
{
    // Convert above to use user input to define patterns
    std::cout << "Enter patterns to search for, separated by spaces: ";
    std::ifstream file("shrek3.txt");
    std::string line;
    std::string result;
    while (std::getline(file, line)) {
        result += line;
    }
    std::string input;
    std::getline(std::cin, input);
    vs patterns;
    std::stringstream ss(input);
    std::string pattern;
    while (std::getline(ss, pattern, ' ')) {
        patterns.push_back(pattern);
    }
    for (auto& p : patterns) {
        std::cout << "Pattern: " << p << std::endl;
    }
    FSM shrek(patterns);
    std::cout << PROMPT;
    std::getline(std::cin, input);
    while (input != "q" && input != "") {
        if (input == "s") {
            vs results = shrek.match(result);
            for (auto& r : results) {
                std::cout << "Match: " << r << std::endl;
            }
        } else {
            vs results = shrek.match(input);
            for (auto& r : results) {
                std::cout << "Match: " << r << std::endl;
            }
        }
        std::cout << PROMPT;
        std::getline(std::cin, input);
    }
}
