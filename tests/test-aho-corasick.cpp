#include "doctest/doctest.h"
#include "aho-corasick.hpp"

TEST_CASE("Test basic functionality")
{
    FSM a({ "abc", "abcd", "ab" });
    CHECK(a.match("abc") == vs({ "ab", "abc" }));
}

TEST_CASE("Test overlapping matching")
{
    FSM a({ "qasim", "aniqa", "mimi" });
    CHECK(a.match("qasimaniqaganiqasimimianimimi") == vs({ "qasim", "aniqa", "aniqa", "qasim", "mimi", "mimi" }));
}

TEST_CASE("Test failure link")
{
    FSM a({ "b", "c", "ab" });
    vs s = a.match("abc");
    CHECK(s == vs({ "ab", "b", "c" }));
}

TEST_CASE("Test large pattern")
{
    std::string s = "";
    for (int i = 0; i < 1000000; i++) {
        s += rand() % 26 + 'a';
    }
    FSM a({ s });
    
}

TEST_CASE("Test many patterns")
{
    vs patterns;
    for (int i = 0; i < 1000000; i++) {
        patterns.push_back(std::to_string(rand() % 26 + 'a'));
    }
    FSM a(patterns);
    std::string s = "";
    for (int i = 0; i < 2000000; i++) {
        s += rand() % 26 + 'a';
    }
    vs results = a.match(s);
}

TEST_CASE("Test substring patterns")
{
    FSM a({ "A", "AG","C","CAA","GAG","GC","GCA"});
    vs results = a.match("GCAA");
    for (auto& r : results) {
        std::cout << r << std::endl;
    }
    CHECK(results == vs({ "GC", "C","GCA","A","CAA","A"}));
}
