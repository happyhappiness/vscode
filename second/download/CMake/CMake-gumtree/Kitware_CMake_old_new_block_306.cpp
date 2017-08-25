{
    // remove any CMakeCache.txt files so we will have a clean test
    std::string ccFile = this->BinaryDirectory + "/CMakeCache.txt";
    cmSystemTools::RemoveFile(ccFile);

    // Choose sources.
    if(!useSources)
      {
      sources.push_back(argv[2]);
      }

    // Detect languages to enable.
    cmGlobalGenerator* gg = this->Makefile->GetGlobalGenerator();
    std::set<std::string> testLangs;
    for(std::vector<std::string>::iterator si = sources.begin();
        si != sources.end(); ++si)
      {
      std::string ext = cmSystemTools::GetFilenameLastExtension(*si);
      std::string lang = gg->GetLanguageFromExtension(ext.c_str());
      if(!lang.empty())
        {
        testLangs.insert(lang);
        }
      else
        {
        std::ostringstream err;
        err << "Unknown extension \"" << ext << "\" for file\n"
            << "  " << *si << "\n"
            << "try_compile() works only for enabled languages.  "
            << "Currently these are:\n  ";
        std::vector<std::string> langs;
        gg->GetEnabledLanguages(langs);
        err << cmJoin(langs, " ");
        err << "\nSee project() command to enable other languages.";
        this->Makefile->IssueMessage(cmake::FATAL_ERROR, err.str());
        return -1;
        }
      }

    // we need to create a directory and CMakeLists file etc...
    // first create the directories
    sourceDirectory = this->BinaryDirectory.c_str();

    // now create a CMakeLists.txt file in that directory
    FILE *fout = cmsys::SystemTools::Fopen(outFileName,"w");
    if (!fout)
      {
      std::ostringstream e;
      e << "Failed to open\n"
        << "  " << outFileName << "\n"
        << cmSystemTools::GetLastSystemError();
      this->Makefile->IssueMessage(cmake::FATAL_ERROR, e.str());
      return -1;
      }

    const char* def = this->Makefile->GetDefinition("CMAKE_MODULE_PATH");
    fprintf(fout, "cmake_minimum_required(VERSION %u.%u.%u.%u)\n",
            cmVersion::GetMajorVersion(), cmVersion::GetMinorVersion(),
            cmVersion::GetPatchVersion(), cmVersion::GetTweakVersion());
    if(def)
      {
      fprintf(fout, "set(CMAKE_MODULE_PATH \"%s\")\n", def);
      }

    std::string projectLangs;
    for(std::set<std::string>::iterator li = testLangs.begin();
        li != testLangs.end(); ++li)
      {
      projectLangs += " " + *li;
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
        }
      }
    fprintf(fout, "project(CMAKE_TRY_COMPILE%s)\n", projectLangs.c_str());
    fprintf(fout, "set(CMAKE_VERBOSE_MAKEFILE 1)\n");
    for(std::set<std::string>::iterator li = testLangs.begin();
        li != testLangs.end(); ++li)
      {
      std::string langFlags = "CMAKE_" + *li + "_FLAGS";
      const char* flags = this->Makefile->GetDefinition(langFlags);
      fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
              cmOutputConverter::EscapeForCMake(flags?flags:"").c_str());
      fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
              " ${COMPILE_DEFINITIONS}\")\n", li->c_str(), li->c_str());
      }
    switch(this->Makefile->GetPolicyStatus(cmPolicies::CMP0056))
      {
      case cmPolicies::WARN:
        if(this->Makefile->PolicyOptionalWarningEnabled(
             "CMAKE_POLICY_WARNING_CMP0056"))
          {
          std::ostringstream w;
          w << cmPolicies::GetPolicyWarning(cmPolicies::CMP0056) << "\n"
            "For compatibility with older versions of CMake, try_compile "
            "is not honoring caller link flags (e.g. CMAKE_EXE_LINKER_FLAGS) "
            "in the test project."
            ;
          this->Makefile->IssueMessage(cmake::AUTHOR_WARNING, w.str());
          }
      case cmPolicies::OLD:
        // OLD behavior is to do nothing.
        break;
      case cmPolicies::REQUIRED_IF_USED:
      case cmPolicies::REQUIRED_ALWAYS:
        this->Makefile->IssueMessage(
          cmake::FATAL_ERROR,
          cmPolicies::GetRequiredPolicyError(cmPolicies::CMP0056)
          );
      case cmPolicies::NEW:
        // NEW behavior is to pass linker flags.
        {
        const char* exeLinkFlags =
          this->Makefile->GetDefinition("CMAKE_EXE_LINKER_FLAGS");
        fprintf(fout, "set(CMAKE_EXE_LINKER_FLAGS %s)\n",
                cmOutputConverter::EscapeForCMake(
                    exeLinkFlags ? exeLinkFlags : "").c_str());
        } break;
      }
    fprintf(fout, "set(CMAKE_EXE_LINKER_FLAGS \"${CMAKE_EXE_LINKER_FLAGS}"
            " ${EXE_LINKER_FLAGS}\")\n");
    fprintf(fout, "include_directories(${INCLUDE_DIRECTORIES})\n");
    fprintf(fout, "set(CMAKE_SUPPRESS_REGENERATION 1)\n");
    fprintf(fout, "link_directories(${LINK_DIRECTORIES})\n");
    // handle any compile flags we need to pass on
    if (!compileDefs.empty())
      {
      fprintf(fout, "add_definitions(%s)\n", cmJoin(compileDefs, " ").c_str());
      }

    /* Use a random file name to avoid rapid creation and deletion
       of the same executable name (some filesystems fail on that).  */
    sprintf(targetNameBuf, "cmTC_%05x",
            cmSystemTools::RandomSeed() & 0xFFFFF);
    targetName = targetNameBuf;

    if (!targets.empty())
      {
      std::string fname = "/" + std::string(targetName) + "Targets.cmake";
      cmExportTryCompileFileGenerator tcfg(gg, targets, this->Makefile);
      tcfg.SetExportFile((this->BinaryDirectory + fname).c_str());
      tcfg.SetConfig(this->Makefile->GetSafeDefinition(
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
      So the user can set CMAKE_OSX_ARCHITECTURES to i386;ppc and then set
      CMAKE_TRY_COMPILE_OSX_ARCHITECTURES first to i386 and then to ppc to
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
    if (const char *cxxDef
              = this->Makefile->GetDefinition("CMAKE_CXX_COMPILER_TARGET"))
      {
      std::string flag="-DCMAKE_CXX_COMPILER_TARGET=";
      flag += cxxDef;
      cmakeFlags.push_back(flag);
      }
    if (const char *cDef
                = this->Makefile->GetDefinition("CMAKE_C_COMPILER_TARGET"))
      {
      std::string flag="-DCMAKE_C_COMPILER_TARGET=";
      flag += cDef;
      cmakeFlags.push_back(flag);
      }
    if (const char *tcxxDef = this->Makefile->GetDefinition(
                                  "CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN"))
      {
      std::string flag="-DCMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN=";
      flag += tcxxDef;
      cmakeFlags.push_back(flag);
      }
    if (const char *tcDef = this->Makefile->GetDefinition(
                                    "CMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN"))
      {
      std::string flag="-DCMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN=";
      flag += tcDef;
      cmakeFlags.push_back(flag);
      }
    if (const char *rootDef
              = this->Makefile->GetDefinition("CMAKE_SYSROOT"))
      {
      std::string flag="-DCMAKE_SYSROOT=";
      flag += rootDef;
      cmakeFlags.push_back(flag);
      }
    if(this->Makefile->GetDefinition("CMAKE_POSITION_INDEPENDENT_CODE")!=0)
      {
      fprintf(fout, "set(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
      }
    if (const char *lssDef = this->Makefile->GetDefinition(
        "CMAKE_LINK_SEARCH_START_STATIC"))
      {
      fprintf(fout, "set(CMAKE_LINK_SEARCH_START_STATIC \"%s\")\n", lssDef);
      }
    if (const char *lssDef = this->Makefile->GetDefinition(
        "CMAKE_LINK_SEARCH_END_STATIC"))
      {
      fprintf(fout, "set(CMAKE_LINK_SEARCH_END_STATIC \"%s\")\n", lssDef);
      }

    /* Set the appropriate policy information for ENABLE_EXPORTS */
    fprintf(fout, "cmake_policy(SET CMP0065 %s)\n",
       this->Makefile->GetPolicyStatus(cmPolicies::CMP0065) ==
         cmPolicies::NEW ? "NEW" : "OLD");
    if(const char *ee = this->Makefile->GetDefinition(
        "CMAKE_ENABLE_EXPORTS"))
      {
      fprintf(fout, "set(CMAKE_ENABLE_EXPORTS %s)\n", ee);
      }

    /* Put the executable at a known location (for COPY_FILE).  */
    fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
            this->BinaryDirectory.c_str());
    /* Create the actual executable.  */
    fprintf(fout, "add_executable(%s", targetName.c_str());
    for(std::vector<std::string>::iterator si = sources.begin();
        si != sources.end(); ++si)
      {
      fprintf(fout, " \"%s\"", si->c_str());

      // Add dependencies on any non-temporary sources.
      if(si->find("CMakeTmp") == si->npos)
        {
        this->Makefile->AddCMakeDependFile(*si);
        }
      }
    fprintf(fout, ")\n");
    if (useOldLinkLibs)
      {
      fprintf(fout,
              "target_link_libraries(%s ${LINK_LIBRARIES})\n",
              targetName.c_str());
      }
    else
      {
      fprintf(fout, "target_link_libraries(%s %s)\n",
              targetName.c_str(),
              libsToLink.c_str());
      }
    fclose(fout);
    projectName = "CMAKE_TRY_COMPILE";
    }