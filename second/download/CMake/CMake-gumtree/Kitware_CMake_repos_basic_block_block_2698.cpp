{
#ifdef TEST_C_FLAGS
    cmFailed(
      "CMake CMAKE_C_FLAGS are being passed to c++ files the compiler!");
#else
    cmPassed("CMake CMAKE_C_FLAGS are not being passed to c++ files.");
#endif
    if (TestCFlags(msg)) {
      cmPassed("CMake CMAKE_C_FLAGS are being passed to c files and CXX flags "
               "are not.");
    } else {
      cmFailed(msg);
    }
  }