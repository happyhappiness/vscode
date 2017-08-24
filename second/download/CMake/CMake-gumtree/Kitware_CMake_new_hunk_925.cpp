      fprintf(fout, "SET(CMAKE_MODULE_PATH %s)\n", def);
      }

    std::string projectLangs;
    for(std::set<std::string>::iterator li = testLangs.begin();
        li != testLangs.end(); ++li)
      {
      projectLangs += " " + *li;
      std::string rulesOverrideBase = "CMAKE_USER_MAKE_RULES_OVERRIDE";
      std::string rulesOverrideLang = rulesOverrideBase + "_" + *li;
      if(const char* rulesOverridePath =
         this->Makefile->GetDefinition(rulesOverrideLang.c_str()))
        {
        fprintf(fout, "SET(%s \"%s\")\n",
                rulesOverrideLang.c_str(), rulesOverridePath);
        }
      else if(const char* rulesOverridePath2 =
              this->Makefile->GetDefinition(rulesOverrideBase.c_str()))
        {
        fprintf(fout, "SET(%s \"%s\")\n",
                rulesOverrideBase.c_str(), rulesOverridePath2);
        }
      }
    fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE%s)\n", projectLangs.c_str());
    fprintf(fout, "SET(CMAKE_VERBOSE_MAKEFILE 1)\n");
    for(std::set<std::string>::iterator li = testLangs.begin();
        li != testLangs.end(); ++li)
      {
      fprintf(fout, "SET(CMAKE_%s_FLAGS \"", li->c_str());
      std::string langFlags = "CMAKE_" + *li + "_FLAGS";
      if(const char* flags = this->Makefile->GetDefinition(langFlags.c_str()))
        {
        fprintf(fout, " %s ", flags);
        }
      fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");
      }
    fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
    fprintf(fout, "SET(CMAKE_SUPPRESS_REGENERATION 1)\n");
    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
