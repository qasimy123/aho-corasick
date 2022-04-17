#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>
#define vs std::vector<std::string>
#define vi std::vector<int>
#define dqi std::deque<int>

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
    std::vector<vi> trie;
    vi failureLink;
    /**
     * @brief Outputs of the automaton.
     */
    vs outputs;

    /**
     * @brief Build the suffix tree.
     */
    void build();
    /**
     * @brief Build the failure links.
     */
    void buildFailure();
    /**
     * @brief Build the trie.
     */
    void buildTrie();
    int go(int state, char c);
    int fail(int state);
    std::string output(int state);
    void extend(const std::string& s, int* newState);
};
