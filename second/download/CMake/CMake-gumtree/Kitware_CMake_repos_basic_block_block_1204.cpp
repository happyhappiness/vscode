{
  int i;
  volatile pid_t* oldForkPIDs;
  for (i = 0; i < KWSYSPE_PIPE_COUNT; ++i) {
    cp->PipeReadEnds[i] = -1;
  }
  for (i = 0; i < 3; ++i) {
    cp->PipeChildStd[i] = -1;
  }
  cp->SignalPipe = -1;
  cp->SelectError = 0;
  cp->StartTime.tv_sec = -1;
  cp->StartTime.tv_usec = -1;
  cp->TimeoutTime.tv_sec = -1;
  cp->TimeoutTime.tv_usec = -1;
  cp->TimeoutExpired = 0;
  cp->PipesLeft = 0;
  cp->CommandsLeft = 0;
#if KWSYSPE_USE_SELECT
  FD_ZERO(&cp->PipeSet);
#endif
  cp->State = kwsysProcess_State_Starting;
  cp->Killed = 0;
  cp->ErrorMessage[0] = 0;

  oldForkPIDs = cp->ForkPIDs;
  cp->ForkPIDs = (volatile pid_t*)malloc(sizeof(volatile pid_t) *
                                         (size_t)(cp->NumberOfCommands));
  if (oldForkPIDs) {
    kwsysProcessVolatileFree(oldForkPIDs);
  }
  if (!cp->ForkPIDs) {
    return 0;
  }
  for (i = 0; i < cp->NumberOfCommands; ++i) {
    cp->ForkPIDs[i] = 0; /* can't use memset due to volatile */
  }

  if (cp->CommandExitCodes) {
    free(cp->CommandExitCodes);
  }
  cp->CommandExitCodes =
    (int*)malloc(sizeof(int) * (size_t)(cp->NumberOfCommands));
  if (!cp->CommandExitCodes) {
    return 0;
  }
  memset(cp->CommandExitCodes, 0,
         sizeof(int) * (size_t)(cp->NumberOfCommands));

  /* Allocate process result information for each process.  */
  free(cp->ProcessResults);
  cp->ProcessResults = (kwsysProcessResults*)malloc(
    sizeof(kwsysProcessResults) * (size_t)(cp->NumberOfCommands));
  if (!cp->ProcessResults) {
    return 0;
  }
  memset(cp->ProcessResults, 0,
         sizeof(kwsysProcessResults) * (size_t)(cp->NumberOfCommands));
  for (i = 0; i < cp->NumberOfCommands; i++) {
    cp->ProcessResults[i].ExitException = kwsysProcess_Exception_None;
    cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Starting;
    cp->ProcessResults[i].ExitCode = 1;
    cp->ProcessResults[i].ExitValue = 1;
    strcpy(cp->ProcessResults[i].ExitExceptionString, "No exception");
  }

  /* Allocate memory to save the real working directory.  */
  if (cp->WorkingDirectory) {
#if defined(MAXPATHLEN)
    cp->RealWorkingDirectoryLength = MAXPATHLEN;
#elif defined(PATH_MAX)
    cp->RealWorkingDirectoryLength = PATH_MAX;
#else
    cp->RealWorkingDirectoryLength = 4096;
#endif
    cp->RealWorkingDirectory =
      (char*)malloc((size_t)(cp->RealWorkingDirectoryLength));
    if (!cp->RealWorkingDirectory) {
      return 0;
    }
  }

  return 1;
}