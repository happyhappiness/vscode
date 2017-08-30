            cmVersion::GetPatchVersion(), cmVersion::GetTweakVersion());

    if(def)

      {

      fprintf(fout, "set(CMAKE_MODULE_PATH %s)\n", def);

      }



    std::string projectLangs;

