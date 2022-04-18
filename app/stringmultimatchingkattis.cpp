#include <algorithm>
#include <cassert>
#include <climits>
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
    vi match(const std::string& string);

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

FSM::FSM(const std::vector<std::string>& s)
{
    // Sort the strings by length.
    this->strings = s;
    size_t n = s.size();
    size_t max_len = 10;
    for (size_t i = 0; i < n; ++i) {
        max_len += s[i].size();
    }
    assert(n < INT_MAX - 1);
    assert(max_len < INT_MAX - 1);
    this->trie = std::vector<std::vector<int>>(max_len, std::vector<int>(MAX_CHAR, -1));
    // initialize output to be unordered_map of empty vector
    this->outputs = std::unordered_map<int, std::vector<std::string>>();
    this->failureLink = std::vector<int>(max_len, 0);
    this->buildTrie();
    this->buildFailure();
}

vi FSM::match(const std::string& s)
{
    int state = 0;
    size_t n = s.length();
    std::unordered_map<std::string, vi> result;
    // initialize result to be unordered_map of empty vector for each string in this->strings
    for (auto& str : this->strings) {
        result[str] = vi();
    }
    for (int i = 0; i < n; i++) {
        while (go(state, s[i]) == -1) {
            state = fail(state);
        }
        state = go(state, s[i]);
        if (output(state).size() > 0) {
            for (std::string& o : output(state)) {
                result.at(o).push_back(i - o.size() + 1);
            }
        }
    }
    for (auto& k : this->strings) {
        for (auto& i : result[k]) {
            std::cout << i << " ";
        }
        std::cout << '\n';
    }
    return {};
}

int FSM::go(int state, char c)
{
    return this->trie[static_cast<size_t>(state)][static_cast<size_t>(c)];
}

int FSM::fail(int state)
{
    return this->failureLink[static_cast<size_t>(state)];
}

vs FSM::output(int state)
{
    // if state is not in the unordered_map, return empty vector
    if (this->outputs.find(state) == this->outputs.end()) {
        return vs();
    }
    return this->outputs[state];
}

void FSM::buildTrie()
{
    int newState = 1;

    for (size_t i = 0; i < this->strings.size(); ++i) {
        std::string s = this->strings[i];
        extend(s, &newState);
    }

    for (size_t i = 0; i < MAX_CHAR; ++i) {
        if (go(0, i) == -1) {
            this->trie[0][i] = 0;
        }
    }
}

void FSM::extend(const std::string& s, int* newState)
{
    int state = 0;
    size_t j = 0;

    while (go(state, s[j]) != -1) {
        state = go(state, s[j]);
        j++;
    }
    for (size_t i = j; i < s.size(); ++i) {
        *newState = *newState + 1;
        this->trie[static_cast<size_t>(state)][static_cast<size_t>(s[i])] = *newState;
        state = *newState;
    }
    this->outputs.emplace(state, vs { s });
}

void FSM::buildFailure()
{
    dqi q;
    for (size_t i = 0; i < MAX_CHAR; ++i) {
        int s = go(0, i);
        if (s != 0) {
            q.push_back(s);
            this->failureLink[static_cast<size_t>(s)] = 0;
        }
    }

    while (!q.empty()) {
        int r = q.front();
        q.pop_front();
        for (size_t i = 0; i < MAX_CHAR; ++i) {
            int s = go(r, i);
            if (s != -1) {
                q.push_back(s);
                int state = fail(r);
                while (go(state, i) == -1) {
                    state = fail(state);
                }
                this->failureLink[static_cast<size_t>(s)] = go(state, i);
                if (this->outputs.find(s) != this->outputs.end()) {
                    for (auto& o : this->outputs[fail(s)]) {
                        this->outputs[s].push_back(o);
                    }
                } else {
                    this->outputs.emplace(s, this->outputs[fail(s)]);
                }
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    while (std::cin >> n) {
        std::string pattern, text;
        vs patterns;
        for (int i = 0; i < n; i++) {
            getline(std::cin, pattern);
            while (pattern == "") {
                getline(std::cin, pattern);
            }
            patterns.push_back(pattern);
        }
        FSM fsm({ patterns });
        getline(std::cin, text);
        fsm.match(text);

        patterns.clear();
    }
    return 0;
}
