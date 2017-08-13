fprintf(
            fout, "set(CMAKE_EXE_LINKER_FLAGS %s)\n",
            cmOutputConverter::EscapeForCMake(exeLinkFlags ? exeLinkFlags : "")
              .c_str())