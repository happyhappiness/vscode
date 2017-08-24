(!kwsysProcessSetNonBlocking(p[0])) {
      kwsysProcessCleanup(cp, 1);
      return;
    }