A very brief description of the algorithm/data structure you implemented. I mean, what
problem or task does it address.
• The O() running time bounds of your implementation: if it is not as good as the running
time bound from the resources you use, explain why you could not attain those bounds (it
may be a very valid excuse: perhaps getting as far as you did is a project on its own!). Note,
some algorithms have complicated O() bounds that are hard to see in practice (eg., intricate
integer factorization methods), but you should do your best to explain what is going on here
anyway.
• A list of all resources you ended up using, you might use more than what was in your proposal.
But even if you didn’t use any more resources, I still want the ones from your proposal listed
1
here.
• Instructions for compiling and running, including how to run the tests you include (more on
this below).
• A description of any peculiarities or assumptions you had to make to get things to work.
Example: if you choose a geometric algorithm then you might want to state something along
the lines of “I only got it working if no three points in the input are collinear”. Another
Example: if it crashes or produces the wrong output in certain cases and you couldn’t hunt
the bug down, let me know.
• A summary of all other files included in your project.
• An explanation of how to interpret the output from your program
## Structure
``` text
.
├── CMakeLists.txt
├── app
│   └── main.cpp
├── include
│   ├── example.h
│   └── exampleConfig.h.in
├── src
│   └── example.cpp
└── tests
    ├── dummy.cpp
    └── main.cpp
```

Sources go in [src/](src/), header files in [include/](include/), main programs in [app/](app), and
tests go in [tests/](tests/) (compiled to `unit_tests` by default).

If you add a new executable, say `app/hello.cpp`, you only need to add the following two lines to [CMakeLists.txt](CMakeLists.txt):

``` cmake
add_executable(main app/main.cpp)   # Name of exec. and location of file.
target_link_libraries(main PRIVATE ${LIBRARY_NAME})  # Link the executable to lib built from src/*.cpp (if it uses it).
```

You can find the example source code that builds the `main` executable in [app/main.cpp](app/main.cpp) under the `Build` section in [CMakeLists.txt](CMakeLists.txt).
If the executable you made does not use the library in [src/](src), then only the first line is needed.



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
