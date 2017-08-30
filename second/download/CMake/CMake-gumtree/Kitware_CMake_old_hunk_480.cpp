              fname.c_str());
    }

    /* for the TRY_COMPILEs we want to be able to specify the architecture.
      So the user can set CMAKE_OSX_ARCHITECTURES to i386;ppc and then set
      CMAKE_TRY_COMPILE_OSX_ARCHITECTURES first to i386 and then to ppc to
      have the tests run for each specific architecture. Since
      cmLocalGenerator doesn't allow building for "the other"
      architecture only via CMAKE_OSX_ARCHITECTURES.
      */
    if (this->Makefile->GetDefinition("CMAKE_TRY_COMPILE_OSX_ARCHITECTURES") !=
        0) {
      std::string flag = "-DCMAKE_OSX_ARCHITECTURES=";
      flag += this->Makefile->GetSafeDefinition(
        "CMAKE_TRY_COMPILE_OSX_ARCHITECTURES");
      cmakeFlags.push_back(flag);
    } else if (this->Makefile->GetDefinition("CMAKE_OSX_ARCHITECTURES") != 0) {
      std::string flag = "-DCMAKE_OSX_ARCHITECTURES=";
      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_ARCHITECTURES");
      cmakeFlags.push_back(flag);
    }
    /* on APPLE also pass CMAKE_OSX_SYSROOT to the try_compile */
    if (this->Makefile->GetDefinition("CMAKE_OSX_SYSROOT") != 0) {
      std::string flag = "-DCMAKE_OSX_SYSROOT=";
      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_SYSROOT");
      cmakeFlags.push_back(flag);
    }
    /* on APPLE also pass CMAKE_OSX_DEPLOYMENT_TARGET to the try_compile */
    if (this->Makefile->GetDefinition("CMAKE_OSX_DEPLOYMENT_TARGET") != 0) {
      std::string flag = "-DCMAKE_OSX_DEPLOYMENT_TARGET=";
      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_DEPLOYMENT_TARGET");
      cmakeFlags.push_back(flag);
    }
    if (const char* cxxDef =
          this->Makefile->GetDefinition("CMAKE_CXX_COMPILER_TARGET")) {
      std::string flag = "-DCMAKE_CXX_COMPILER_TARGET=";
      flag += cxxDef;
      cmakeFlags.push_back(flag);
    }
    if (const char* cDef =
          this->Makefile->GetDefinition("CMAKE_C_COMPILER_TARGET")) {
      std::string flag = "-DCMAKE_C_COMPILER_TARGET=";
      flag += cDef;
      cmakeFlags.push_back(flag);
    }
    if (const char* tcxxDef = this->Makefile->GetDefinition(
          "CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN")) {
      std::string flag = "-DCMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN=";
      flag += tcxxDef;
      cmakeFlags.push_back(flag);
    }
    if (const char* tcDef = this->Makefile->GetDefinition(
          "CMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN")) {
      std::string flag = "-DCMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN=";
      flag += tcDef;
      cmakeFlags.push_back(flag);
    }
    if (const char* rootDef = this->Makefile->GetDefinition("CMAKE_SYSROOT")) {
      std::string flag = "-DCMAKE_SYSROOT=";
      flag += rootDef;
      cmakeFlags.push_back(flag);
    }
    if (this->Makefile->GetDefinition("CMAKE_POSITION_INDEPENDENT_CODE") !=
        0) {
      fprintf(fout, "set(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
    }
    if (const char* lssDef =
          this->Makefile->GetDefinition("CMAKE_LINK_SEARCH_START_STATIC")) {
      fprintf(fout, "set(CMAKE_LINK_SEARCH_START_STATIC \"%s\")\n", lssDef);
    }
    if (const char* lssDef =
          this->Makefile->GetDefinition("CMAKE_LINK_SEARCH_END_STATIC")) {
      fprintf(fout, "set(CMAKE_LINK_SEARCH_END_STATIC \"%s\")\n", lssDef);
    }

    /* Set the appropriate policy information for ENABLE_EXPORTS */
