            this->BinaryDirectory.c_str());

    /* Create the actual executable.  */

    fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",source.c_str());

    fprintf(fout, 

            "TARGET_LINK_LIBRARIES(cmTryCompileExec ${LINK_LIBRARIES})\n");

    fclose(fout);

    projectName = "CMAKE_TRY_COMPILE";

    targetName = "cmTryCompileExec";

    // if the source is not in CMakeTmp 

    if(source.find("CMakeTmp") == source.npos)

      {

      this->Makefile->AddCMakeDependFile(source.c_str());

      }

    

    }

  // else the srcdir bindir project target signature

  else

    {

    projectName = argv[3].c_str();

    

    if (argv.size() - extraArgs == 5)

      {

      targetName = argv[4].c_str();

      }

    }

  

  bool erroroc = cmSystemTools::GetErrorOccuredFlag();

  cmSystemTools::ResetErrorOccuredFlag();

  std::string output;

  // actually do the try compile now that everything is setup

  int res = this->Makefile->TryCompile(sourceDirectory, 

                                       this->BinaryDirectory.c_str(),

                                       projectName, 

                                       targetName, 

                                       this->SrcFileSignature,

                                       &cmakeFlags, 

                                       &output);

  if ( erroroc )

    {

    cmSystemTools::SetErrorOccured();

    }

  

  // set the result var to the return value to indicate success or failure

  this->Makefile->AddCacheDefinition(argv[0].c_str(),

                                     (res == 0 ? "TRUE" : "FALSE"),

