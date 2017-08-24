{
  size_t i;

  if (!hProcess || hProcess == INVALID_HANDLE_VALUE) {
    return;
  }

  EnterCriticalSection(&kwsysProcesses.Lock);

  /* Find the given process in the set.  */
  for (i = 0; i < kwsysProcesses.Count; ++i) {
    if (kwsysProcesses.Processes[i].hProcess == hProcess) {
      break;
    }
  }
  if (i < kwsysProcesses.Count) {
    /* Found it!  Remove the process from the set.  */
    --kwsysProcesses.Count;
    for (; i < kwsysProcesses.Count; ++i) {
      kwsysProcesses.Processes[i] = kwsysProcesses.Processes[i + 1];
    }

    /* If this was the last process, free the array.  */
    if (kwsysProcesses.Count == 0) {
      kwsysProcesses.Size = 0;
      free(kwsysProcesses.Processes);
      kwsysProcesses.Processes = 0;
    }
  }

  LeaveCriticalSection(&kwsysProcesses.Lock);
}