(cp->State == kwsysProcess_State_Exception) {
    return cp->ProcessResults[cp->NumberOfCommands - 1].ExitExceptionString;
  }