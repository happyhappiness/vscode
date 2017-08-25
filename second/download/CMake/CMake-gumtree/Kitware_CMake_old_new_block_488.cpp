{
      fprintf(fout, "ADD_DEFINITIONS( ");
      for (size_t i = 0; i < compileDefs.size(); ++i)
        {
        fprintf(fout,"%s ",compileDefs[i].c_str());
        }
      fprintf(fout, ")\n");
      }