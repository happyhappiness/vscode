(cp->Terminated) {
    KWSYSPE_DEBUG((stderr, "interrupt: child already terminated\n"));
    return;
  }