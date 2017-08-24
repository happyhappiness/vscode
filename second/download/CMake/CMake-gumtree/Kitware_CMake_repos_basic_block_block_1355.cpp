(i = 0; i < cp->NumberOfCommands; ++i) {
    ResumeThread(cp->ProcessInformation[i].hThread);
  }