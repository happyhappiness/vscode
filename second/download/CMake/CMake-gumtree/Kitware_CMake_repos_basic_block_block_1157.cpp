{
    int r;
    if (!getcwd(cp->RealWorkingDirectory,
                (size_t)(cp->RealWorkingDirectoryLength))) {
      kwsysProcessCleanup(cp, 1);
      return;
    }

    /* Some platforms specify that the chdir call may be
       interrupted.  Repeat the call until it finishes.  */
    while (((r = chdir(cp->WorkingDirectory)) < 0) && (errno == EINTR))
      ;
    if (r < 0) {
      kwsysProcessCleanup(cp, 1);
      return;
    }
  }