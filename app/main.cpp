#include "aho-corasick.hpp"
#include <fstream>
#include <iostream>
#include <stdlib.h>

/*
 * Simple main program that demontrates the usage of the Aho-Corasick on
 * the full script of Shrek 3. Src: https://github.com/mackenziedg/shrek/blob/master/data/shrek3.txt
 */
int main()
{
    std::ifstream file("shrek3.txt");
    std::string line;
    std::string result;
    FSM shrek({ "cry", "Wow", "Magic" });
    while (std::getline(file, line)) {
        result += line;
    }
    vs results = shrek.match(result);
    for (auto& r : results) {
        std::cout << "Match: " << r << std::endl;
    }
}
