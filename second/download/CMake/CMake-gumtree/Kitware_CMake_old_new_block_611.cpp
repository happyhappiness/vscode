{
    // remove any CMakeCache.txt files so we will have a clean test
    std::string ccFile = this->BinaryDirectory + "/CMakeCache.txt";
    cmSystemTools::RemoveFile(ccFile.c_str());

    // we need to create a directory and CMakeLists file etc...
    // first create the directories
    sourceDirectory = this->BinaryDirectory.c_str();

    // now create a CMakeLists.txt file in that directory
    FILE *fout = fopen(outFileName.c_str(),"w");
    if (!fout)
      {
      cmOStringStream e;
      e << "Failed to open\n"
        << "  " << outFileName.c_str() << "\n"
        << cmSystemTools::GetLastSystemError();
      this->Makefile->IssueMessage(cmake::FATAL_ERROR, e.str());
      return -1;
      }

    std::string source = argv[2];
    std::string ext = cmSystemTools::GetFilenameLastExtension(source);
    const char* lang =(this->Makefile->GetCMakeInstance()->GetGlobalGenerator()
                        ->GetLanguageFromExtension(ext.c_str()));
    const char* def = this->Makefile->GetDefinition("CMAKE_MODULE_PATH");
    fprintf(fout, "cmake_minimum_required(VERSION %u.%u.%u.%u)\n",
            cmVersion::GetMajorVersion(), cmVersion::GetMinorVersion(),
            cmVersion::GetPatchVersion(), cmVersion::GetTweakVersion());
    if(def)
      {
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
    // handle any compile flags we need to pass on
    if (compileDefs.size())
      {
      fprintf(fout, "ADD_DEFINITIONS( ");
      for (size_t i = 0; i < compileDefs.size(); ++i)
        {
        fprintf(fout,"%s ",compileDefs[i].c_str());
        }
      fprintf(fout, ")\n");
      }

    /* Use a random file name to avoid rapid creation and deletion
       of the same executable name (some filesystems fail on that).  */
    sprintf(targetNameBuf, "cmTryCompileExec%u",
            cmSystemTools::RandomSeed());
    targetName = targetNameBuf;

    if (!targets.empty())
      {
      std::string fname = "/" + std::string(targetName) + "Targets.cmake";
      cmExportTryCompileFileGenerator tcfg;
      tcfg.SetExportFile((this->BinaryDirectory + fname).c_str());
      tcfg.SetExports(targets);
      tcfg.SetConfig(this->Makefile->GetDefinition(
                                          "CMAKE_TRY_COMPILE_CONFIGURATION"));

      if(!tcfg.GenerateImportFile())
        {
        this->Makefile->IssueMessage(cmake::FATAL_ERROR,
                                     "could not write export file.");
        fclose(fout);
        return -1;
        }
      fprintf(fout,
              "\ninclude(\"${CMAKE_CURRENT_LIST_DIR}/%s\")\n\n",
              fname.c_str());
      }

    /* for the TRY_COMPILEs we want to be able to specify the architecture.
      So the user can set CMAKE_OSX_ARCHITECTURE to i386;ppc and then set
      CMAKE_TRY_COMPILE_OSX_ARCHITECTURE first to i386 and then to ppc to
      have the tests run for each specific architecture. Since
      cmLocalGenerator doesn't allow building for "the other"
      architecture only via CMAKE_OSX_ARCHITECTURES.
      */
    if(this->Makefile->GetDefinition("CMAKE_TRY_COMPILE_OSX_ARCHITECTURES")!=0)
      {
      std::string flag="-DCMAKE_OSX_ARCHITECTURES=";
      flag += this->Makefile->GetSafeDefinition(
                                        "CMAKE_TRY_COMPILE_OSX_ARCHITECTURES");
      cmakeFlags.push_back(flag);
      }
    else if (this->Makefile->GetDefinition("CMAKE_OSX_ARCHITECTURES")!=0)
      {
      std::string flag="-DCMAKE_OSX_ARCHITECTURES=";
      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_ARCHITECTURES");
      cmakeFlags.push_back(flag);
      }
    /* on APPLE also pass CMAKE_OSX_SYSROOT to the try_compile */
    if(this->Makefile->GetDefinition("CMAKE_OSX_SYSROOT")!=0)
      {
      std::string flag="-DCMAKE_OSX_SYSROOT=";
      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_SYSROOT");
      cmakeFlags.push_back(flag);
      }
    /* on APPLE also pass CMAKE_OSX_DEPLOYMENT_TARGET to the try_compile */
    if(this->Makefile->GetDefinition("CMAKE_OSX_DEPLOYMENT_TARGET")!=0)
      {
      std::string flag="-DCMAKE_OSX_DEPLOYMENT_TARGET=";
      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_DEPLOYMENT_TARGET");
      cmakeFlags.push_back(flag);
      }
    if(this->Makefile->GetDefinition("CMAKE_POSITION_INDEPENDENT_CODE")!=0)
      {
      fprintf(fout, "SET(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
      }

    /* Put the executable at a known location (for COPY_FILE).  */
    fprintf(fout, "SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
            this->BinaryDirectory.c_str());
    /* Create the actual executable.  */
    fprintf(fout, "ADD_EXECUTABLE(%s \"%s\")\n", targetName, source.c_str());
    if (useOldLinkLibs)
      {
      fprintf(fout,
              "TARGET_LINK_LIBRARIES(%s ${LINK_LIBRARIES})\n",targetName);
      }
    else
      {
      fprintf(fout, "TARGET_LINK_LIBRARIES(%s %s)\n",
              targetName,
              libsToLink.c_str());
      }
    fclose(fout);
    projectName = "CMAKE_TRY_COMPILE";
    // if the source is not in CMakeTmp
    if(source.find("CMakeTmp") == source.npos)
      {
      this->Makefile->AddCMakeDependFile(source.c_str());
      }

    }