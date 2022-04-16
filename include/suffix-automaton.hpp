#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define vs std::vector<std::string>
#define vi std::vector<int>

/**
 * @brief This class implements a suffix automaton.
 *
 */
class Automaton {
public:
    /**
     * @brief Construct a new Automaton object.
     * @param strings The strings to be processed.
     */
    Automaton(const vs& strings);
    /**
     * @brief Match a string against the automaton.
     * @param string The string to be matched.
     * @return true If the string matches the automaton.
     * @return false If the string does not match the automaton.
     */
    bool match(const std::string& string);

private:
    /**
     * @brief The strings to be processed.
     */
    vs strings;
    /**
     * @brief The suffix tree.
     */
    std::vector<vi> tree;
    /**
     * @brief The suffix links.
     */
    vi links;
    /**
     * @brief The number of strings.
     */
    int n;
    /**
     * @brief The number of characters in the longest string.
     */
    int m;
    /**
     * @brief Build the suffix tree.
     */
    void build();
    /**
     * @brief Build the suffix links.
     */
    void buildLinks();
};
