              ? "NEW"
              : "OLD");

    if (targetType == cmState::EXECUTABLE) {
      /* Put the executable at a known location (for COPY_FILE).  */
      fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
              this->BinaryDirectory.c_str());
      /* Create the actual executable.  */
      fprintf(fout, "add_executable(%s", targetName.c_str());
    } else // if (targetType == cmState::STATIC_LIBRARY)
    {
      /* Put the static library at a known location (for COPY_FILE).  */
      fprintf(fout, "set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \"%s\")\n",
