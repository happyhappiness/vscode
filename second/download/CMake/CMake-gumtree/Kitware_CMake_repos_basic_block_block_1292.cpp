{
          memcpy(newProcesses.Processes, oldProcesses.Processes,
                 ((size_t)(oldProcesses.Count) * sizeof(kwsysProcess*)));
        }