(cp->State == kwsysProcess_State_Error) {
    /* The error message is already in its buffer.  Tell
       kwsysProcessCleanup to not create it.  */
    kwsysProcessCleanup(cp, 0);
    return 1;
  }