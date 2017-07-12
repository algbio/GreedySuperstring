# compact-superstring

Use a greedy approximation algorithm to find the shortest common superstring of given strings in succinct space.

## Build/Runtime Requirements

- Reasonably new compilers for C and C++, e.g. GCC 6 or Clang 3.7. C++14 support is required.
- GNU gengetopt 2.22.6.

On Linux also the following libraries are required to build and run a tool to verify the constructed superstring:

- [libBlocksRuntime](https://github.com/mheily/blocks-runtime)
- [libpthread_workqueue](https://github.com/mheily/libpwq)
- [libkqueue](https://github.com/mheily/libkqueue)

## Build Requirements

- [CMake](http://cmake.org)
- [Boost](http://www.boost.org)
- [Python2](http://python.org) to build the verification tool for Linux.

## Building

### Short version

1. `git clone https://github.com/tsnorri/compact-superstring.git`
2. `cd compact-superstring`
3. `git submodule update --init`
4. `touch local.mk`
5. `make -j4 BUILD_STYLE=release`

### Long version

1. Clone the repository with `git clone https://github.com/tsnorri/compact-superstring.git`.
2. Change the working directory with `cd compact-superstring`.
3. Run `git submodule update --init`. This clones the missing submodules and updates their working tree.
5. Edit `local.mk` in the repository root to override build variables. Useful variables include `CC` and `CXX` for C and C++ compilers respectively, `LOCAL_CXXFLAGS` and `LOCAL_LDFLAGS` for C++ and linker flags respectively and `BOOST_IOSTREAMS_LIB` for the command line options to link Boost's Iostreams library. See `common.mk` for additional variables.
5. Run make with a suitable numer of parallel jobs and the variable `BUILD_STYLE` defined, e.g. `make -j4 BUILD_STYLE=release`

Useful make targets include:

<dl>
<dt>all</dt>
<dd>Build everything</dd>

<dt>clean</dt>
<dd>Remove build products except for dependencies (in the `lib` folder).</dd>

<dt>clean-all</dt>
<dd>Remove all build products.</dd>
</dl>


## Running

Please see `run.sh` for examples.

The tool `tribble/find-superstring/find-superstring` takes a FASTA file as input and generates an index. The index may then be used to generate the superstring.

The tool `tribble/verify-superstring/verify-superstring` takes the superstring generated by `find-superstring` as input and builds another index. This index may then be used to check that all the reads in the original FASTA input file are substrings of the superstring.

See `tribble/find-superstring/find-superstring --help` and `tribble/verify-superstring/verify-superstring --help` for command line options and examples.
