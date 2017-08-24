(TestCFlags(msg)) {
      cmPassed("CMake CMAKE_C_FLAGS are being passed to c files and CXX flags "
               "are not.");
    } else {
      cmFailed(msg);
    }