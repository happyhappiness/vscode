            cmVersion::GetPatchVersion(), cmVersion::GetTweakVersion());

    if(def)

      {

      fprintf(fout, "SET(CMAKE_MODULE_PATH %s)\n", def);

      }



    std::string projectLangs;

