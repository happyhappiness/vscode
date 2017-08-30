      return -1;

      }



    std::string source = argv[2];

    std::string ext = cmSystemTools::GetFilenameLastExtension(source);

    const char* lang =(this->Makefile->GetCMakeInstance()->GetGlobalGenerator()

                        ->GetLanguageFromExtension(ext.c_str()));

    const char* def = this->Makefile->GetDefinition("CMAKE_MODULE_PATH");

    fprintf(fout, "cmake_minimum_required(VERSION %u.%u.%u.%u)\n",

            cmVersion::GetMajorVersion(), cmVersion::GetMinorVersion(),

