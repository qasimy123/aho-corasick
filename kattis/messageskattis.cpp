#include "aho-corasick.hpp"

std::vector<std::pair<int, int>> FSM::matchRanges(const std::string& s)
{
    int state = 0;
    size_t n = s.length();
    std::vector<std::pair<int, int>> ret;
    for (int i = 0; i < n; i++) {
        while (go(state, s[i]) == -1) {
            state = fail(state);
        }
        state = go(state, s[i]);
        if (output(state).size() > 0) {
            for (auto& o : output(state)) {
                ret.push_back(std::make_pair(i - o.size() + 1, i));
            }
        }
    }
    return ret;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string s;
    std::cin >> s;
    vs patterns;
    while (s != "#") {
        patterns.push_back(s);
        std::cin >> s;
    }
    FSM fsm(patterns);
    std::cin >> s;
    while (s != "#") {
        // read until last character of the string is "|"
        std::string new_s = "";
        while (s[s.size() - 1] != '|') {
            new_s += s;
            std::cin >> s;
        }
        new_s += s;
        std::vector<std::pair<int, int>> ret = fsm.matchRanges(new_s);
        // https://www.geeksforgeeks.org/maximal-disjoint-intervals/
        // Find max set of non-overlapping intervals
        // first sort by end
        std::sort(ret.begin(), ret.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });
        int count = 0;
        if (ret.size() > 0) {
            count = 1;
            int start = ret[0].second;
            for (size_t i = 1; i < ret.size(); ++i) {
                if (ret[i].first > start) {
                    count++;
                    start = ret[i].second;
                }
            }
        } else {
            count = 0;
        }

        std::cout << count << "\n";
        std::cin >> s;
    }
    return 0;
}
