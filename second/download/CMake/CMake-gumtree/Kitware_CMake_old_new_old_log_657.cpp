fprintf(fout, "set(CMAKE_EXE_LINKER_FLAGS %s)\n",
                cmLocalGenerator::EscapeForCMake(
                    exeLinkFlags ? exeLinkFlags : "").c_str());