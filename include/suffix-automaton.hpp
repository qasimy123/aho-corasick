#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define vs std::vector<std::string>
#define vi std::vector<int>
#define dqi std::deque<int>
#define MAX_CHAR 126

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
    vs match(const std::string& string);

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
    /**
     * @brief Goes to the trie node corresponding to the given state and character.
     * @param state The state.
     * @param c The character.
     * @return The trie node corresponding to the given state and character.
     */
    int go(int state, char c);
    /**
     * @brief Returns the failure link of the given state.
     * @param state The state.
     * @return The failure link of the given state.
     */
    int fail(int state);
    /**
     * @brief Returns the output of the given state.
     * @param state The state.
     * @return The output of the given state.
     */
    std::string output(int state);
    /**
     * @brief Adds a string to the trie.
     * @param s The string to be added.
     * @param newState The state of the trie prior to the addition.
     */
    void extend(const std::string& s, int* newState);
};
