                           outFileName.c_str());
      return -1;
      }
    fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE)\n");
    fprintf(fout, "IF (CMAKE_ANSI_CXXFLAGS)\n");
    fprintf(fout, "  SET(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} ${CMAKE_ANSI_CXXFLAGS}\")\n");
    fprintf(fout, "  SET(CMAKE_C_FLAGS \"${CMAKE_C_FLAGS} ${CMAKE_ANSI_CFLAGS}\")\n");
    fprintf(fout, "ENDIF (CMAKE_ANSI_CXXFLAGS)\n");
    // handle any compile flags we need to pass on
    if (compileFlags.size())
      {
