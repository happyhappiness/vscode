fprintf(fout, "SET(CMAKE_%s_FLAGS %s)\n", li->c_str(),
              lg->EscapeForCMake(flags?flags:"").c_str());