fprintf(fout, "set(CMAKE_EXE_LINKER_FLAGS %s)\n",
                lg->EscapeForCMake(exeLinkFlags?exeLinkFlags:"").c_str());