                cmPolicies::NEW
              ? "NEW"
              : "OLD");
    if (const char* ee =
          this->Makefile->GetDefinition("CMAKE_ENABLE_EXPORTS")) {
      fprintf(fout, "set(CMAKE_ENABLE_EXPORTS %s)\n", ee);
    }

    if (targetType == cmState::EXECUTABLE) {
      /* Put the executable at a known location (for COPY_FILE).  */