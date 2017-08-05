fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
              cmOutputConverter::EscapeForCMake(flags?flags:"").c_str());