{
  if (!kwsysProcessesInitialize() || !hProcess ||
      hProcess == INVALID_HANDLE_VALUE) {
    return 0;
  }

  /* Enter the critical section. */
  EnterCriticalSection(&kwsysProcesses.Lock);

  /* Make sure there is enough space for the new process handle.  */
  if (kwsysProcesses.Count == kwsysProcesses.Size) {
    size_t newSize;
    kwsysProcessInstance* newArray;
    /* Start with enough space for a small number of process handles
       and double the size each time more is needed.  */
    newSize = kwsysProcesses.Size ? kwsysProcesses.Size * 2 : 4;

    /* Try allocating the new block of memory.  */
    if (newArray = (kwsysProcessInstance*)malloc(
          newSize * sizeof(kwsysProcessInstance))) {
      /* Copy the old process handles to the new memory.  */
      if (kwsysProcesses.Count > 0) {
        memcpy(newArray, kwsysProcesses.Processes,
               kwsysProcesses.Count * sizeof(kwsysProcessInstance));
      }
    } else {
      /* Failed to allocate memory for the new process handle set.  */
      LeaveCriticalSection(&kwsysProcesses.Lock);
      return 0;
    }

    /* Free original array. */
    free(kwsysProcesses.Processes);

    /* Update original structure with new allocation. */
    kwsysProcesses.Size = newSize;
    kwsysProcesses.Processes = newArray;
  }

  /* Append the new process information to the set.  */
  kwsysProcesses.Processes[kwsysProcesses.Count].hProcess = hProcess;
  kwsysProcesses.Processes[kwsysProcesses.Count].dwProcessId = dwProcessid;
  kwsysProcesses.Processes[kwsysProcesses.Count++].NewProcessGroup =
    newProcessGroup;

  /* Leave critical section and return success. */
  LeaveCriticalSection(&kwsysProcesses.Lock);

  return 1;
}