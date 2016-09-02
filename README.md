## Game of Life

Simple C++ implementation of John Conway's Game of Life, including a parallelised OpenMP branch.

## Build

Dependencies: Boost, STL, C++11, OpenMP (for OpenMP branch).

On some platforms, it is necessary to set CMAKE_INCLUDE_PATH and CMAKE_LIBRARY_PATH to include the correct version of Boost. This might happen when Boost is in a non-standard location (FindBoost.cmake cannot find it) or when compiling with gcc on OSX (needs gcc-compiled Boost, not clang-compiled).

In-source or out-of-source:

` mkdir build
` cd build
` cmake path/to/source
` make

## Tests

Implemented using Catch. Tests are fairly self-explanatory.

` cd /path/to/build/test
` ./test

## Local Execution

` cd /path/to/build/bin
` ./game_of_life --frames [number of iterations to simulate] --out [output path and prefix, e.g. preexisting_output_dir/outprefix-] --init [initialisation data]

For example:

` ./game_of_life --frames 2 --out output/big_output_ --init ../test/test_grid_1024.txt

## Remote Deployment/Execution

Remote deployment/execution is done using ssh, for systems set up with the Sun Grid Engine (qsub job submission). First, edit /path/to/build/bin/connect_ssh.sh to be have the form:

` ssh username@server

`deploy.sh` deploys to that server and builds the project. `run_remote.sh` submits an example job using the deployed version of `submit_qsub.sh`.

Once the cluster job has finished, call `fetch_results.sh` to retrieve the output data.
