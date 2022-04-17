#include "suffix-automaton.hpp"

Automaton::Automaton(const std::vector<std::string>& s)
{
    this->strings = s;
    size_t n = s.size();
    size_t max_len = 1;
    for (size_t i = 0; i < n; ++i) {
        max_len += s[i].size();
    }
    this->trie = std::vector<std::vector<int>>(max_len, std::vector<int>(26, -1));
    this->outputs = std::vector<std::string>(max_len, "");
    this->failureLink = std::vector<int>(max_len, -1);
    this->buildTrie();
    this->buildFailure();
}

bool Automaton::match(const std::string& s)
{
    int state = 0;
    size_t n = s.size();

    for (size_t i = 0; i < n; i++) {
        while (go(state, s[i] - 97) == -1) {
            state = fail(state);
        }
        state = go(state, s[i] - 97);
        if (output(state) != "") {
            std::cout << "output: " << output(state) << " i: " << i << std::endl;
        }
    }
    return true;
}

int Automaton::go(int state, char c)
{
    return this->trie[static_cast<size_t>(state)][static_cast<size_t>(c)];
}

int Automaton::fail(int state)
{
    return this->failureLink[static_cast<size_t>(state)];
}

std::string Automaton::output(int state)
{
    return this->outputs[static_cast<size_t>(state)];
}

void Automaton::buildTrie()
{
    std::cout << "Building trie..." << std::endl;
    int newState = 0;

    for (size_t i = 0; i < this->strings.size(); ++i) {
        std::string s = this->strings[i];
        extend(s, &newState);
    }

    for (char i = 0; i < 26; ++i) {
        if (go(0, i) == -1) {
            this->trie[0][static_cast<size_t>(i)] = 0;
        }
    }
    
}

void Automaton::extend(const std::string& s, int* newState)
{
    int state = 0;
    size_t j = 0;

    while (go(state, s[j] - 97) != -1) {
        state = go(state, s[j] - 97);
        j++;
    }
    for (size_t i = j; i < s.size(); ++i) {
        *newState = *newState + 1;
        this->trie[static_cast<size_t>(state)][static_cast<size_t>(s[i] - 'a')] = *newState;
        state = *newState;
    }
    this->outputs[static_cast<size_t>(state)] = s;
}

void Automaton::buildFailure()
{
    std::cout << "Building failure..." << std::endl;
    dqi q;
    for (char i = 0; i < 26; ++i) {
        int s = go(0, i);
        if (s != 0) {
            q.push_back(s);
            this->failureLink[static_cast<size_t>(s)] = 0;
        }
    }

    while (!q.empty()) {
        int r = q.front();
        q.pop_front();
        for (char i = 0; i < 26; ++i) {
            int s = go(r, i);
            if (s != -1) {
                q.push_back(s);
                int state = fail(r);
                while (go(state, i) == -1) {
                    state = fail(state);
                }
                this->failureLink[static_cast<size_t>(s)] = go(state, i);
                this->outputs[static_cast<size_t>(s)] = this->outputs[static_cast<size_t>(s)]+this->outputs[static_cast<size_t>(fail(s))];
            }
        }
    }
    
}
