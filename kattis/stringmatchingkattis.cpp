#include "aho-corasick.hpp"

vi FSM::matchIndex(const std::string& s)
{
    int state = 0;
    size_t n = s.length();
    vi result;
    for (size_t i = 0; i < n; i++) {
        while (go(state, s[i]) == -1) {
            state = fail(state);
        }
        state = go(state, s[i]);
        if (output(state).size() > 0) {
            for (auto& o : output(state)) {
                result.push_back(static_cast<int>(i - o.size() + 1));
            }
        }
    }
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string pattern, text;
    getline(std::cin, pattern);
    while (pattern != "") {
        FSM fsm({ pattern });
        getline(std::cin, text);
        vi result = fsm.matchIndex(text);
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i] << " ";
        }
        std::cout << "\n";
        getline(std::cin, pattern);
    }
}