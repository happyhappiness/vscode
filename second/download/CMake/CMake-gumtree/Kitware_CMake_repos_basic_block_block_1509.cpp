(kwsysProcesses.Count == 0) {
      kwsysProcesses.Size = 0;
      free(kwsysProcesses.Processes);
      kwsysProcesses.Processes = 0;
    }