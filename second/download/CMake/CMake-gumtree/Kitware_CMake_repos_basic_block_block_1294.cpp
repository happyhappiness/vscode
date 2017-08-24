(newProcesses.Processes != oldProcesses.Processes) {
      free(oldProcesses.Processes);
    }