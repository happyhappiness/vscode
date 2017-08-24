{
    /* This failed for some reason.  Kill the suspended process. */
    TerminateProcess(cp->ProcessInformation[index].hProcess, 1);
    /* And clean up... */
    kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hProcess);
    kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hThread);
    strcpy(cp->ErrorMessage, "kwsysProcessesAdd function failed");
    error = ERROR_NOT_ENOUGH_MEMORY; /* Most likely reason.  */
  }