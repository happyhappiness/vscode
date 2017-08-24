{
    *pfile = (char*)malloc(strlen(file) + 1);
    if (!*pfile) {
      return 0;
    }
    strcpy(*pfile, file);
  }