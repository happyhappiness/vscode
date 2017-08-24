{
      /* Failed to allocate memory for the new process handle set.  */
      LeaveCriticalSection(&kwsysProcesses.Lock);
      return 0;
    }