{
    SetCurrentDirectoryW(cp->RealWorkingDirectory);
    free(cp->RealWorkingDirectory);
    cp->RealWorkingDirectory = 0;
  }