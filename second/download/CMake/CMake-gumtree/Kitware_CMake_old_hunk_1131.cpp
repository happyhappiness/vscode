      fprintf(fout, "SET(CMAKE_MODULE_PATH %s)\n", def);
      }

    const char* rulesOverrideBase = "CMAKE_USER_MAKE_RULES_OVERRIDE";
    std::string rulesOverrideLang =
      rulesOverrideBase + (lang ? std::string("_") + lang : std::string(""));
    if(const char* rulesOverridePath =
       this->Makefile->GetDefinition(rulesOverrideLang.c_str()))
      {
      fprintf(fout, "SET(%s \"%s\")\n",
              rulesOverrideLang.c_str(), rulesOverridePath);
      }
    else if(const char* rulesOverridePath2 =
            this->Makefile->GetDefinition(rulesOverrideBase))
      {
      fprintf(fout, "SET(%s \"%s\")\n",
              rulesOverrideBase, rulesOverridePath2);
      }

    if(lang)
      {
      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE %s)\n", lang);
      }
    else
      {
      fclose(fout);
      cmOStringStream err;
      err << "Unknown extension \"" << ext << "\" for file\n"
          << "  " << source << "\n"
          << "try_compile() works only for enabled languages.  "
          << "Currently these are:\n ";
      std::vector<std::string> langs;
      this->Makefile->GetCMakeInstance()->GetGlobalGenerator()->
        GetEnabledLanguages(langs);
      for(std::vector<std::string>::iterator l = langs.begin();
          l != langs.end(); ++l)
        {
        err << " " << *l;
        }
      err << "\nSee project() command to enable other languages.";
      this->Makefile->IssueMessage(cmake::FATAL_ERROR, err.str());
      return -1;
      }
    std::string langFlags = "CMAKE_";
    langFlags +=  lang;
    langFlags += "_FLAGS";
    fprintf(fout, "SET(CMAKE_VERBOSE_MAKEFILE 1)\n");
    fprintf(fout, "SET(CMAKE_%s_FLAGS \"", lang);
    const char* flags = this->Makefile->GetDefinition(langFlags.c_str());
    if(flags)
      {
      fprintf(fout, " %s ", flags);
      }
    fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");
    fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
    fprintf(fout, "SET(CMAKE_SUPPRESS_REGENERATION 1)\n");
    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
