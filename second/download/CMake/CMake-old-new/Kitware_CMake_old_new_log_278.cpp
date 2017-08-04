fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
              cmLocalGenerator::EscapeForCMake(flags?flags:"").c_str())