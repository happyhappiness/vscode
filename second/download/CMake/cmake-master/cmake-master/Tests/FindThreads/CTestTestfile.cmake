# CMake generated Testfile for 
# Source directory: /data/download/cmake/cmake-master/Tests/FindThreads
# Build directory: /data/download/cmake/cmake-master/Tests/FindThreads
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(FindThreads.C-only "/data/download/cmake/cmake-master/bin/ctest" "--build-and-test" "/data/download/cmake/cmake-master/Tests/FindThreads/C-only" "/data/download/cmake/cmake-master/Tests/FindThreads/C-only" "--build-generator" "Unix Makefiles" "--build-project" "FindThreads_C-only" "--build-options" "-DCMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/make" "--test-command" "/data/download/cmake/cmake-master/bin/ctest" "-V")
add_test(FindThreads.CXX-only "/data/download/cmake/cmake-master/bin/ctest" "--build-and-test" "/data/download/cmake/cmake-master/Tests/FindThreads/CXX-only" "/data/download/cmake/cmake-master/Tests/FindThreads/CXX-only" "--build-generator" "Unix Makefiles" "--build-project" "FindThreads_CXX-only" "--build-options" "-DCMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/make" "--test-command" "/data/download/cmake/cmake-master/bin/ctest" "-V")
