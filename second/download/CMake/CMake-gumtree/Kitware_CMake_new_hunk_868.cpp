      if(const char* rulesOverridePath =
         this->Makefile->GetDefinition(rulesOverrideLang.c_str()))
        {
        fprintf(fout, "set(%s \"%s\")\n",
                rulesOverrideLang.c_str(), rulesOverridePath);
        }
      else if(const char* rulesOverridePath2 =
              this->Makefile->GetDefinition(rulesOverrideBase.c_str()))
        {
        fprintf(fout, "set(%s \"%s\")\n",
                rulesOverrideBase.c_str(), rulesOverridePath2);
        }
      }
    fprintf(fout, "project(CMAKE_TRY_COMPILE%s)\n", projectLangs.c_str());
    fprintf(fout, "set(CMAKE_VERBOSE_MAKEFILE 1)\n");
    for(std::set<std::string>::iterator li = testLangs.begin();
        li != testLangs.end(); ++li)
      {
      std::string langFlags = "CMAKE_" + *li + "_FLAGS";
      const char* flags = this->Makefile->GetDefinition(langFlags.c_str());
      fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
              lg->EscapeForCMake(flags?flags:"").c_str());
      fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
              " ${COMPILE_DEFINITIONS}\")\n", li->c_str(), li->c_str());
      }
    fprintf(fout, "include_directories(${INCLUDE_DIRECTORIES})\n");
    fprintf(fout, "set(CMAKE_SUPPRESS_REGENERATION 1)\n");
    fprintf(fout, "link_directories(${LINK_DIRECTORIES})\n");
    // handle any compile flags we need to pass on
    if (compileDefs.size())
      {
      fprintf(fout, "add_definitions( ");
      for (size_t i = 0; i < compileDefs.size(); ++i)
        {
        fprintf(fout,"%s ",compileDefs[i].c_str());
