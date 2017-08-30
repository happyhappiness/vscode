    fprintf(fout, "set(CMAKE_SUPPRESS_REGENERATION 1)\n");

    fprintf(fout, "link_directories(${LINK_DIRECTORIES})\n");

    // handle any compile flags we need to pass on

    if (compileDefs.size())

      {

      fprintf(fout, "add_definitions( ");

      for (size_t i = 0; i < compileDefs.size(); ++i)

