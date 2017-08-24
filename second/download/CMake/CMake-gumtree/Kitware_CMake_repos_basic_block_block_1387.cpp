(expired) {
    /* A timeout has expired.  */
    if (user) {
      /* The user timeout has expired.  It has no time left.  */
      return kwsysProcess_Pipe_Timeout;
    } else {
      /* The process timeout has expired.  Kill the child now.  */
      KWSYSPE_DEBUG((stderr, "killing child because timeout expired\n"));
      kwsysProcess_Kill(cp);
      cp->TimeoutExpired = 1;
      cp->Killed = 0;
      return kwsysProcess_Pipe_None;
    }
  }