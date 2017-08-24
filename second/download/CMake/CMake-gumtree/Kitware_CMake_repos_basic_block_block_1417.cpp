(cp->Terminated) {
    KWSYSPE_DEBUG((stderr, "kill: child already terminated\n"));
    return;
  }