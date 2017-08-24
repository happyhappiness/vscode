(pipe(p KWSYSPE_VMS_NONBLOCK) < 0) {
      kwsysProcessCleanup(cp, 1);
      return;
    }