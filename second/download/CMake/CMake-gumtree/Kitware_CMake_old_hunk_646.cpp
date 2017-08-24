    fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
            this->BinaryDirectory.c_str());
    /* Create the actual executable.  */
    fprintf(fout, "add_executable(%s", targetName);
    for(std::vector<std::string>::iterator si = sources.begin();
        si != sources.end(); ++si)
      {
