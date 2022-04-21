#include "aho-corasick.hpp"

vi FSM::matchIndex(const std::string& s)
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
        fsm.matchIndex(text);

        patterns.clear();
    }
    return 0;
}
