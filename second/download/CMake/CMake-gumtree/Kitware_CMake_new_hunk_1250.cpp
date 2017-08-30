    const char* lang =(this->Makefile->GetCMakeInstance()->GetGlobalGenerator()

                        ->GetLanguageFromExtension(ext.c_str()));

    const char* def = this->Makefile->GetDefinition("CMAKE_MODULE_PATH");

    fprintf(fout, "cmake_minimum_required(VERSION %u.%u.%u.%u)\n",

            cmVersion::GetMajorVersion(), cmVersion::GetMinorVersion(),

            cmVersion::GetPatchVersion(), cmVersion::GetTweakVersion());

    if(def)

      {

      fprintf(fout, "SET(CMAKE_MODULE_PATH %s)\n", def);

