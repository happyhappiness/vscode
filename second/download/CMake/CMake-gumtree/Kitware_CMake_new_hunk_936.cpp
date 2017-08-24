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
        return -1;
        }
      fprintf(fout,
              "\ninclude(\"${CMAKE_CURRENT_LIST_DIR}/%s\")\n\n",
              fname.c_str());
      }

    /* for the TRY_COMPILEs we want to be able to specify the architecture.
      So the user can set CMAKE_OSX_ARCHITECTURE to i386;ppc and then set
      CMAKE_TRY_COMPILE_OSX_ARCHITECTURE first to i386 and then to ppc to
