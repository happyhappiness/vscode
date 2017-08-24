{
    /* Open a file for the child's stdin to read.  */
    cp->PipeChildStd[0] = open(cp->PipeFileSTDIN, O_RDONLY);
    if (cp->PipeChildStd[0] < 0) {
      kwsysProcessCleanup(cp, 1);
      return;
    }

    /* Set close-on-exec flag on the pipe's end.  */
    if (fcntl(cp->PipeChildStd[0], F_SETFD, FD_CLOEXEC) < 0) {
      kwsysProcessCleanup(cp, 1);
      return;
    }
  }