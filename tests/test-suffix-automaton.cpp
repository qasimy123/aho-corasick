#include "doctest/doctest.h"
#include "suffix-automaton.hpp"

TEST_CASE("complicated integration tests could be here")
{
  Automaton a({"abc", "abcd", "ab"});
  CHECK(a.match("abcd"));
  
}
