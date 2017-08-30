        const char* exeLinkFlags =
          this->Makefile->GetDefinition("CMAKE_EXE_LINKER_FLAGS");
        fprintf(fout, "set(CMAKE_EXE_LINKER_FLAGS %s)\n",
                cmOutputConverter::EscapeForCMake(
                    exeLinkFlags ? exeLinkFlags : "").c_str());
        } break;
      }