{
  int i;

  /* Make sure we are executing a detached process.  */
  if (!cp || !cp->Detached || cp->State != kwsysProcess_State_Executing ||
      cp->TimeoutExpired || cp->Killed || cp->Terminated) {
    return;
  }

  /* Disable the reading threads.  */
  kwsysProcessDisablePipeThreads(cp);

  /* Wait for all pipe threads to reset.  */
  for (i = 0; i < KWSYSPE_PIPE_COUNT; ++i) {
    WaitForSingleObject(cp->Pipe[i].Reader.Reset, INFINITE);
    WaitForSingleObject(cp->Pipe[i].Waker.Reset, INFINITE);
  }

  /* We will not wait for exit, so cleanup now.  */
  kwsysProcessCleanup(cp, 0);

  /* The process has been disowned.  */
  cp->State = kwsysProcess_State_Disowned;
}