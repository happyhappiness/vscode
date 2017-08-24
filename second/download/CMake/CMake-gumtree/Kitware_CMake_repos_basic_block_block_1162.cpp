{
      /* The process timeout has expired.  Kill the children now.  */
      kwsysProcess_Kill(cp);
      cp->Killed = 0;
      cp->TimeoutExpired = 1;
      return kwsysProcess_Pipe_None;
    }