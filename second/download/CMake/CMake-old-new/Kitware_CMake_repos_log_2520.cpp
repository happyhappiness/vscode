fprintf(fout, "set(%s %s)\n", langFlagsCfg.c_str(),
                  cmOutputConverter::EscapeForCMake(flagsCfg ? flagsCfg : "")
                    .c_str())