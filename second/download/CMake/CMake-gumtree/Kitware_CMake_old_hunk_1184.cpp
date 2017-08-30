  }

  if (!success) {
    if (ignoreErrors) {
      //printf("\n-- RC file %i dependencies in %s\n\n", includes.size(), dfile.c_str());
      outputDepFile(dfile, objfile, includes);
    }
    return exit_code;
  }

