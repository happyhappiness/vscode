      std::string langFlags = "CMAKE_" + *li + "_FLAGS";

      const char* flags = this->Makefile->GetDefinition(langFlags);

      fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),

              cmLocalGenerator::EscapeForCMake(flags?flags:"").c_str());

      fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"

              " ${COMPILE_DEFINITIONS}\")\n", li->c_str(), li->c_str());

      }

