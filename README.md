### Aho–Corasick algorithm

The Aho–Corasick algorithm is a dictionary-matching algorithm invented by Alfred V. Aho and Margaret J. Corasick. It constructs a finite state machine that uses a trie of all patterns to quickly finds all matches instead of backtracking to check all possible matches as the naive algorithm does. This matching is done by keeping track of partial matches and using this information to speed up the search process.

[![Coverage Status](https://coveralls.io/repos/github/qasimy123/aho-corasick/badge.svg?branch=master)](https://coveralls.io/github/qasimy123/aho-corasick?branch=master) [![Build Status](https://app.travis-ci.com/qasimy123/aho-corasick.svg?branch=master)](https://app.travis-ci.com/qasimy123/aho-corasick)

## Time Complexity

The algorithm takes O(|patterns|) time to build the finite state machine where |patterns| is proportional to the length of all the patterns, and the algorithm takes O(|text|) time to search the text for matches. [2]

## References

[1]“Elsevier Enhanced Reader.” https://reader.elsevier.com/reader/sd/pii/S0304397509002370?token=928633D737A0E588F2ED7F3E430D0350097DD01B4397486F60CDA25DA8C1A7EBE3EF2B82C716B4156B053E6CA8716C66&originRegion=us-east-1&originCreation=20220416003051 (accessed Apr. 15, 2022).
[2]A. V. Aho and M. J. Corasick, “Efficient string matching: an aid to bibliographic search,” Commun. ACM, vol. 18, no. 6, pp. 333–340, Jun. 1975, doi: 10.1145/360825.360855.
[3]M. Crochemore and C. Hancart, “Automata for Matching Patterns,” in Handbook of Formal Languages, G. Rozenberg and A. Salomaa, Eds. Berlin, Heidelberg: Springer Berlin Heidelberg, 1997, pp. 399–462. doi: 10.1007/978-3-662-07675-0_9.
[4]Tharaka Dimalsha, Aho - Corasick Algorithm, (Apr. 18, 2021). Accessed: Apr. 15, 2022. [Online Video]. Available: https://www.youtube.com/watch?v=m3PDS3rxhoc
[5]Niema Moshiri, Advanced Data Structures: Aho-Corasick Automaton, (Apr. 26, 2020). Accessed: Apr. 15, 2022. [Online Video]. Available: https://www.youtube.com/watch?v=O7_w001f58c

Boilerplate from:
https://github.com/bsamseth/cpp-project

## Structure
To main program is a simple interactive shell that allows the user to enter patterns and text to search. The program then prints out the matches. You can also search the patterns within the full script for shrek 3.

The source code for Aho-Corasick is in the `src` directory.
I also used the same code for 3 kattis problems, those can be found in the `kattis` directory.
They only override the match method for problem specific purposes.

``` text
.
├── CMakeLists.txt
├── app
│   ├── main.cpp
│   └── shrek3.txt
├── include
│   ├── aho-corasick.hpp
├── src
│   └── aho-corasick.cpp
└── tests
│   ├── test-aho-corasick.cpp
│   └── main.cpp
└── kattis
    ├── aho-corasick.cpp # Copy of aho-corasick.cpp in src
    ├── aho-corasick.hpp # Copy of aho-corasick.hpp in include
    ├── stringmatchingkattis.cpp
    ├── stringmultimatchingkattis.cpp
    └── messageskattis.cpp
```

## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Example:

``` bash
> mkdir build && cd build
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make
> ./main
> make test      # Makes and runs the tests.
> make coverage  # Generate a coverage report.
> make doc       # Generate html documentation.
```
