      return -1;

      }



    fprintf(fout, "SET(CMAKE_C_FLAGS \"${CMAKE_C_FLAGS} ${COMPILE_DEFINITIONS}\"\")\n");

    fprintf(fout, "SET(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} ${COMPILE_DEFINITIONS}\")\n");

    fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");

    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");

    // handle any compile flags we need to pass on

