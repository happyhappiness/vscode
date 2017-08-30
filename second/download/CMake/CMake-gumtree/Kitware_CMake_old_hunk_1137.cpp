    fprintf(fout, "SET(CMAKE_SUPPRESS_REGENERATION 1)\n");
    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
    // handle any compile flags we need to pass on
    if (compileFlags.size())
      {
      fprintf(fout, "ADD_DEFINITIONS( ");
      for (i = 0; i < compileFlags.size(); ++i)
        {
        fprintf(fout,"%s ",compileFlags[i].c_str());
        }
      fprintf(fout, ")\n");
      }
