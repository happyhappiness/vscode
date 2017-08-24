(!cp->OptionDetach) {
    if (!kwsysProcessesAdd(cp)) {
      kwsysProcessCleanup(cp, 1);
      return;
    }
  }