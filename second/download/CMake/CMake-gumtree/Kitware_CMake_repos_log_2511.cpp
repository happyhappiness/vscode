fprintf(fout, "set_property(TARGET %s PROPERTY %s %s)\n", targetName.c_str(),
          cmOutputConverter::EscapeForCMake(prop).c_str(),
          cmOutputConverter::EscapeForCMake(value).c_str())