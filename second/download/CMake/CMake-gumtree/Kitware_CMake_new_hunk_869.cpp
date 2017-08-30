      }

    if(this->Makefile->GetDefinition("CMAKE_POSITION_INDEPENDENT_CODE")!=0)

      {

      fprintf(fout, "set(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");

      }



    /* Put the executable at a known location (for COPY_FILE).  */

    fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",

            this->BinaryDirectory.c_str());

    /* Create the actual executable.  */

    fprintf(fout, "add_executable(%s", targetName);

    for(std::vector<std::string>::iterator si = sources.begin();

        si != sources.end(); ++si)

      {

