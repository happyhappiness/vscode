(cp->NumberOfCommands < 1) {
    strcpy(cp->ErrorMessage, "No command");
    cp->State = kwsysProcess_State_Error;
    return;
  }