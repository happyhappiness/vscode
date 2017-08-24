{
        /* Remove from global list of processes and close handles.  */
        kwsysProcessesRemove(cp->ProcessInformation[i].hProcess);
        kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
        kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hProcess);
      }