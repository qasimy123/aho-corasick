#include "aho-corasick.hpp"
#include <cassert>
#include <climits>

FSM::FSM(const std::vector<std::string>& s)
{
    // Sort the strings by length.
    this->strings = s;
    std::sort(this->strings.begin(), this->strings.end(),
        [](const std::string& a, const std::string& b) {
            return a.size() < b.size();
        });
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
    this->failureLink = std::vector<int>(max_len, -1);
    this->buildTrie();
    this->buildFailure();
    std::cout << "FSM built" << std::endl;
}

vs FSM::match(const std::string& s)
{
    int state = 0;
    size_t n = s.length();
    vs result;
    for (size_t i = 0; i < n; i++) {
        while (go(state, s[i]) == -1) {
            state = fail(state);
        }
        state = go(state, s[i]);
        if (output(state).size() > 0) {
            for (auto& o : output(state)) {
                result.push_back(o);
            }
        }
    }
    return result;
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
    // if state is not in the map, return empty vector
    if (this->outputs.find(state) == this->outputs.end()) {
        return vs();
    }
    return this->outputs[state];
}

void FSM::buildTrie()
{
    std::cout << "Building trie..." << std::endl;
    int newState = 1;

    for (size_t i = 0; i < this->strings.size(); ++i) {
        std::string s = this->strings[i];
        extend(s, &newState);
    }

    for (char i = 0; i < MAX_CHAR; ++i) {
        if (go(0, i) == -1) {
            this->trie[0][static_cast<size_t>(i)] = 0;
        }
    }
}

void FSM::extend(const std::string& s, int* newState)
{
    std::cout << "Extending " << s << std::endl;
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
    std::cout << "Building failure..." << std::endl;
    dqi q;
    for (char i = 0; i < MAX_CHAR; ++i) {
        int s = go(0, i);
        if (s != 0) {
            q.push_back(s);
            this->failureLink[static_cast<size_t>(s)] = 0;
        }
    }

    while (!q.empty()) {
        int r = q.front();
        q.pop_front();
        for (char i = 0; i < MAX_CHAR; ++i) {
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
