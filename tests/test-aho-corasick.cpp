#include "doctest/doctest.h"
#include "aho-corasick.hpp"

TEST_CASE("Test basic functionality")
{
    FSM a({ "abc", "abcd", "ab" });
    CHECK(a.match("abc") == std::vector<std::string>({ "ab", "abc" }));
}

TEST_CASE("Test advanced functionality")
{
    FSM a({ "qasim", "aniqa", "mimi" });
    CHECK(a.match("qasimaniqaganiqasimimianimimi") == std::vector<std::string>({ "qasim", "aniqa", "aniqa", "qasim", "mimi", "mimi" }));
}

TEST_CASE("Test advanced functionality 2")
{
    FSM a({ "b", "c", "ab" });
    vs s = a.match("abc");
    CHECK(s == std::vector<std::string>({ "ab", "b", "c" }));
}
