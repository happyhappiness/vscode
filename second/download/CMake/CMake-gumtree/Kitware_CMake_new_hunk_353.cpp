              fname.c_str());
    }

    // Forward a set of variables to the inner project cache.
    {
      std::set<std::string> vars;
      vars.insert(kCMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN);
      vars.insert(kCMAKE_C_COMPILER_TARGET);
      vars.insert(kCMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN);
      vars.insert(kCMAKE_CXX_COMPILER_TARGET);
      vars.insert(kCMAKE_ENABLE_EXPORTS);
      vars.insert(kCMAKE_LINK_SEARCH_END_STATIC);
      vars.insert(kCMAKE_LINK_SEARCH_START_STATIC);
      vars.insert(kCMAKE_OSX_ARCHITECTURES);
      vars.insert(kCMAKE_OSX_DEPLOYMENT_TARGET);
      vars.insert(kCMAKE_OSX_SYSROOT);
      vars.insert(kCMAKE_POSITION_INDEPENDENT_CODE);
      vars.insert(kCMAKE_SYSROOT);

      /* for the TRY_COMPILEs we want to be able to specify the architecture.
         So the user can set CMAKE_OSX_ARCHITECTURES to i386;ppc and then set
         CMAKE_TRY_COMPILE_OSX_ARCHITECTURES first to i386 and then to ppc to
         have the tests run for each specific architecture. Since
         cmLocalGenerator doesn't allow building for "the other"
         architecture only via CMAKE_OSX_ARCHITECTURES.
         */
      if (const char* tcArchs = this->Makefile->GetDefinition(
            kCMAKE_TRY_COMPILE_OSX_ARCHITECTURES)) {
        vars.erase(kCMAKE_OSX_ARCHITECTURES);
        std::string flag = "-DCMAKE_OSX_ARCHITECTURES=" + std::string(tcArchs);
        cmakeFlags.push_back(flag);
      }

      for (std::set<std::string>::iterator vi = vars.begin(); vi != vars.end();
           ++vi) {
        std::string const& var = *vi;
        if (const char* val = this->Makefile->GetDefinition(var)) {
          std::string flag = "-D" + var + "=" + val;
          cmakeFlags.push_back(flag);
        }
      }
    }

    /* Set the appropriate policy information for ENABLE_EXPORTS */
