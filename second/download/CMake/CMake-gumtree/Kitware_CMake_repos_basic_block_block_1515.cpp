{
      DWORD groupId = kwsysProcesses.Processes[i].dwProcessId;
      if (groupId) {
        GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, groupId);
      }
    }