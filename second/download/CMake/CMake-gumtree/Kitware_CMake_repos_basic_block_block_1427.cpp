{
  int i;
  /* Reset internal status flags.  */
  cp->TimeoutExpired = 0;
  cp->Terminated = 0;
  cp->Killed = 0;

  free(cp->ProcessResults);
  /* Allocate process result information for each process.  */
  cp->ProcessResults = (kwsysProcessResults*)malloc(
    sizeof(kwsysProcessResults) * (cp->NumberOfCommands));
  if (!cp->ProcessResults) {
    return 0;
  }
  ZeroMemory(cp->ProcessResults,
             sizeof(kwsysProcessResults) * cp->NumberOfCommands);
  for (i = 0; i < cp->NumberOfCommands; i++) {
    cp->ProcessResults[i].ExitException = kwsysProcess_Exception_None;
    cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Starting;
    cp->ProcessResults[i].ExitCode = 1;
    cp->ProcessResults[i].ExitValue = 1;
    strcpy(cp->ProcessResults[i].ExitExceptionString, "No exception");
  }

  /* Allocate process information for each process.  */
  free(cp->ProcessInformation);
  cp->ProcessInformation = (PROCESS_INFORMATION*)malloc(
    sizeof(PROCESS_INFORMATION) * cp->NumberOfCommands);
  if (!cp->ProcessInformation) {
    return 0;
  }
  ZeroMemory(cp->ProcessInformation,
             sizeof(PROCESS_INFORMATION) * cp->NumberOfCommands);
  if (cp->CommandExitCodes) {
    free(cp->CommandExitCodes);
  }
  cp->CommandExitCodes = (DWORD*)malloc(sizeof(DWORD) * cp->NumberOfCommands);
  if (!cp->CommandExitCodes) {
    return 0;
  }
  ZeroMemory(cp->CommandExitCodes, sizeof(DWORD) * cp->NumberOfCommands);

  /* Allocate event wait array.  The first event is cp->Full, the rest
     are the process termination events.  */
  cp->ProcessEvents =
    (PHANDLE)malloc(sizeof(HANDLE) * (cp->NumberOfCommands + 1));
  if (!cp->ProcessEvents) {
    return 0;
  }
  ZeroMemory(cp->ProcessEvents, sizeof(HANDLE) * (cp->NumberOfCommands + 1));
  cp->ProcessEvents[0] = cp->Full;
  cp->ProcessEventsLength = cp->NumberOfCommands + 1;

  /* Allocate space to save the real working directory of this process.  */
  if (cp->WorkingDirectory) {
    cp->RealWorkingDirectoryLength = GetCurrentDirectoryW(0, 0);
    if (cp->RealWorkingDirectoryLength > 0) {
      cp->RealWorkingDirectory =
        malloc(cp->RealWorkingDirectoryLength * sizeof(wchar_t));
      if (!cp->RealWorkingDirectory) {
        return 0;
      }
    }
  }
  {
    for (i = 0; i < 3; ++i) {
      cp->PipeChildStd[i] = INVALID_HANDLE_VALUE;
    }
  }

  return 1;
}