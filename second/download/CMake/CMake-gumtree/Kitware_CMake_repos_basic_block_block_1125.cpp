(i = 0; i < cp->NumberOfCommands; ++i) {
      /* Setup the process's pipes.  */
      si.StdIn = nextStdIn;
      if (i == cp->NumberOfCommands - 1) {
        nextStdIn = -1;
        si.StdOut = cp->PipeChildStd[1];
      } else {
        /* Create a pipe to sit between the children.  */
        int p[2] = { -1, -1 };
        if (pipe(p KWSYSPE_VMS_NONBLOCK) < 0) {
          if (nextStdIn != cp->PipeChildStd[0]) {
            kwsysProcessCleanupDescriptor(&nextStdIn);
          }
          kwsysProcessCleanup(cp, 1);
          return;
        }

        /* Set close-on-exec flag on the pipe's ends.  */
        if ((fcntl(p[0], F_SETFD, FD_CLOEXEC) < 0) ||
            (fcntl(p[1], F_SETFD, FD_CLOEXEC) < 0)) {
          close(p[0]);
          close(p[1]);
          if (nextStdIn != cp->PipeChildStd[0]) {
            kwsysProcessCleanupDescriptor(&nextStdIn);
          }
          kwsysProcessCleanup(cp, 1);
          return;
        }
        nextStdIn = p[0];
        si.StdOut = p[1];
      }
      si.StdErr = cp->MergeOutput ? cp->PipeChildStd[1] : cp->PipeChildStd[2];

      {
        int res = kwsysProcessCreate(cp, i, &si);

        /* Close our copies of pipes used between children.  */
        if (si.StdIn != cp->PipeChildStd[0]) {
          kwsysProcessCleanupDescriptor(&si.StdIn);
        }
        if (si.StdOut != cp->PipeChildStd[1]) {
          kwsysProcessCleanupDescriptor(&si.StdOut);
        }
        if (si.StdErr != cp->PipeChildStd[2] && !cp->MergeOutput) {
          kwsysProcessCleanupDescriptor(&si.StdErr);
        }

        if (!res) {
          kwsysProcessCleanupDescriptor(&si.ErrorPipe[0]);
          kwsysProcessCleanupDescriptor(&si.ErrorPipe[1]);
          if (nextStdIn != cp->PipeChildStd[0]) {
            kwsysProcessCleanupDescriptor(&nextStdIn);
          }
          kwsysProcessCleanup(cp, 1);
          return;
        }
      }
    }