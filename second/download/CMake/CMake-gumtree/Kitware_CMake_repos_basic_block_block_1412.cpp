(cp->ProcessInformation) {
      for (i = 0; i < cp->NumberOfCommands; ++i) {
        /* Make sure the process handle isn't closed (e.g. from disowning). */
        if (cp->ProcessInformation[i].hProcess) {
          /* The user created a process group for this process.  The group ID
             is the process ID for the original process in the group.  Note
             that we have to use Ctrl+Break: Ctrl+C is not allowed for process
             groups.  */
          GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT,
                                   cp->ProcessInformation[i].dwProcessId);
        }
      }
    }