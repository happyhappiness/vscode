{
    cp->WorkingDirectory = (char*)malloc(strlen(dir) + 1);
    if (!cp->WorkingDirectory) {
      return 0;
    }
    strcpy(cp->WorkingDirectory, dir);
  }