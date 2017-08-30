      fprintf(fout, "SET(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
      }

    /* Use a random file name to avoid rapid creation and deletion
       of the same executable name (some filesystems fail on that).  */
    sprintf(targetNameBuf, "cmTryCompileExec%u",
            cmSystemTools::RandomSeed());
    targetName = targetNameBuf;

    /* Put the executable at a known location (for COPY_FILE).  */
    fprintf(fout, "SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
            this->BinaryDirectory.c_str());
    /* Create the actual executable.  */
    fprintf(fout, "ADD_EXECUTABLE(%s \"%s\")\n", targetName, source.c_str());
    fprintf(fout, "TARGET_LINK_LIBRARIES(%s ${LINK_LIBRARIES})\n",targetName);
    fclose(fout);
    projectName = "CMAKE_TRY_COMPILE";
    // if the source is not in CMakeTmp