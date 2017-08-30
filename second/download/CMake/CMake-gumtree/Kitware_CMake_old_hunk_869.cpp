      }
    if(this->Makefile->GetDefinition("CMAKE_POSITION_INDEPENDENT_CODE")!=0)
      {
      fprintf(fout, "SET(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
      }

    /* Put the executable at a known location (for COPY_FILE).  */
    fprintf(fout, "SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
            this->BinaryDirectory.c_str());
    /* Create the actual executable.  */
    fprintf(fout, "ADD_EXECUTABLE(%s", targetName);
    for(std::vector<std::string>::iterator si = sources.begin();
        si != sources.end(); ++si)
      {
