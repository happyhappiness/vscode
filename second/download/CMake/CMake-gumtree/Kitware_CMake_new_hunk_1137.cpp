    fprintf(fout, "SET(CMAKE_SUPPRESS_REGENERATION 1)\n");

    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");

    // handle any compile flags we need to pass on

    if (compileDefs.size())

      {

      fprintf(fout, "ADD_DEFINITIONS( ");

      for (size_t i = 0; i < compileDefs.size(); ++i)

        {

        fprintf(fout,"%s ",compileDefs[i].c_str());

        }

      fprintf(fout, ")\n");

      }

