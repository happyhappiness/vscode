(!kwsysProcessesAdd(cp)) {
      kwsysProcessCleanup(cp, 1);
      return;
    }