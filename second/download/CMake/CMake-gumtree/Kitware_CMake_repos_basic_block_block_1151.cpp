(fcntl(cp->PipeChildStd[0], F_SETFD, FD_CLOEXEC) < 0) {
      kwsysProcessCleanup(cp, 1);
      return;
    }