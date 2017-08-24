    {
    if(exception != kwsysProcess_GetExitException(kp))
      {
      fprintf(stderr, "Mismatch in exit exception.  Should have been %d.\n",
              exception);
      }
    if(value != kwsysProcess_GetExitValue(kp))
      {
      fprintf(stderr, "Mismatch in exit value.  Should have been %d.\n",
              value);
      }
    }
  
  if(kwsysProcess_GetState(kp) != state)
    {
    fprintf(stderr, "Mismatch in state.  Should have been %d.\n", state);
    result = 1;
    }
  
