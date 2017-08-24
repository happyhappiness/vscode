{
  /* Make sure a detached child process is running.  */
  if (!cp || !cp->Detached || cp->State != kwsysProcess_State_Executing ||
      cp->TimeoutExpired || cp->Killed) {
    return;
  }

  /* Close all the pipes safely.  */
  kwsysProcessClosePipes(cp);

  /* We will not wait for exit, so cleanup now.  */
  kwsysProcessCleanup(cp, 0);

  /* The process has been disowned.  */
  cp->State = kwsysProcess_State_Disowned;
}