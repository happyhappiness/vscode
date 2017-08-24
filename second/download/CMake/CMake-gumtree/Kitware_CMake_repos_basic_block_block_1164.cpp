(wd.Expired) {
    /* A timeout has expired.  */
    if (wd.User) {
      /* The user timeout has expired.  It has no time left.  */
      return kwsysProcess_Pipe_Timeout;
    } else {
      /* The process timeout has expired.  Kill the children now.  */
      kwsysProcess_Kill(cp);
      cp->Killed = 0;
      cp->TimeoutExpired = 1;
      return kwsysProcess_Pipe_None;
    }
  }