      std::string rulesOverrideBase = "CMAKE_USER_MAKE_RULES_OVERRIDE";

      std::string rulesOverrideLang = rulesOverrideBase + "_" + *li;

      if(const char* rulesOverridePath =

         this->Makefile->GetDefinition(rulesOverrideLang))

        {

        fprintf(fout, "set(%s \"%s\")\n",

                rulesOverrideLang.c_str(), rulesOverridePath);

        }

      else if(const char* rulesOverridePath2 =

              this->Makefile->GetDefinition(rulesOverrideBase))

        {

        fprintf(fout, "set(%s \"%s\")\n",

                rulesOverrideBase.c_str(), rulesOverridePath2);

