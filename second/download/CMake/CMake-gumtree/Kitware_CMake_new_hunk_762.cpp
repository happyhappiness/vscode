    fprintf(stderr, "[%s]\n", i->c_str());

    }

#endif

  // Short-circuit if there is nothing to do.

  if(this->FindRootPathMode == RootPathModeNever)

    {

    return;

    }



  const char* sysroot =

    this->Makefile->GetDefinition("CMAKE_SYSROOT");

  const char* rootPath =

