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
#define vpi std::vector<std::pair<int, int>>
#define MAX_CHAR 128

/**
 * @brief This class implements the aho-corasick algorithm.
 *
 */
class FSM {
public:
    /**
     * @brief Construct a new FSM object.
     * @param strings The strings to be processed. 
     * Must be ASCII strings with no control characters.
     * The combined length of all strings must also be less than INT_MAX-1.
     * Tested upto 1000000 characters.
     * The number of strings must be less than INT_MAX-1.
     * Tested upto 1000000 strings.
     */
    FSM(const vs& strings);
    /**
     * @brief Match a string against the FSM.
     * @param string The string to be matched.
     * @return true If the string matches the FSM.
     * @return false If the string does not match the FSM.
     */
    vs match(const std::string& string);
    vpi matchRanges(const std::string& string);
    vi matchIndex(const std::string& string);

private:
    /**
     * @brief The strings to be processed.
     */
    vs strings;
    /**
     * @brief The trie that holds the patterns.
     */
    std::vector<vi> trie;
    vi failureLink;
    /**
     * @brief Outputs of the FSM.
     */
    std::unordered_map<int, vs> outputs;

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
    vs output(int state);
    /**
     * @brief Adds a string to the trie.
     * @param s The string to be added.
     * @param newState The state of the trie prior to the addition.
     */
    void extend(const std::string& s, int* newState);
};
