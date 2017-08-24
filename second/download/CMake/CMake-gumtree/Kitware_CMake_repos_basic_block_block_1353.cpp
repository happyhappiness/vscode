(i = 0; i < cp->NumberOfCommands; ++i) {
    kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
  }