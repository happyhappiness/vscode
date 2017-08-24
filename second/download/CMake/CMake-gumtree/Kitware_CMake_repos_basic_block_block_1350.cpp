{
  if (!(cp && cp->ProcessResults && (cp->NumberOfCommands > 0))) {
    return "GetExceptionString called with NULL process management structure";
  } else if (cp->State == kwsysProcess_State_Exception) {
    return cp->ProcessResults[cp->NumberOfCommands - 1].ExitExceptionString;
  }
  return "No exception";
}