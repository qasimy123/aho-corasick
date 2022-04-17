#include "doctest/doctest.h"
#include "aho-corasick.hpp"

TEST_CASE("complicated integration tests could be here")
{
    FSM a({ "abc", "abcd", "ab" });
    CHECK(a.match("abc") == std::vector<std::string>({ "ab", "abc" }));
}
