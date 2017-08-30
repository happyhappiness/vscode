    fprintf(fout, "SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
            this->BinaryDirectory.c_str());
    /* Create the actual executable.  */
    fprintf(fout, "ADD_EXECUTABLE(%s", targetName);
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
