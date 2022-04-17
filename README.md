### Aho–Corasick algorithm

The Aho–Corasick algorithm is a dictionary-matching algorithm invented by Alfred V. Aho and Margaret J. Corasick. It constructs a finite state machine that uses a trie of all patterns to quickly finds all matches instead of backtracking to check all possible matches as the naive algorithm does. This matching is done by keeping track of partial matches and using this information to speed up the search process.

## Time Complexity

The algorithm takes O(|patterns|) time to build the finite state machine, and the algorithm takes O(|text|) time to search the text for matches.

## References

## Structure
``` text
.
├── CMakeLists.txt
├── app
│   └── main.cpp
│   └── shrek3.txt
├── include
│   ├── aho-corasick.hpp
├── src
│   └── aho-corasick.cpp
└── tests
    ├── test-aho-corasick.cpp
    └── main.cpp
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
