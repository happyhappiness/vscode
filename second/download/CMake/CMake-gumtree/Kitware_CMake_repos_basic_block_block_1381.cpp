(cp->PipeFileSTDIN) {
    /* Create a handle to read a file for stdin.  */
    wchar_t* wstdin = kwsysEncoding_DupToWide(cp->PipeFileSTDIN);
    DWORD error;
    cp->PipeChildStd[0] =
      CreateFileW(wstdin, GENERIC_READ | GENERIC_WRITE,
                  FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
    error = GetLastError(); /* Check now in case free changes this.  */
    free(wstdin);
    if (cp->PipeChildStd[0] == INVALID_HANDLE_VALUE) {
      kwsysProcessCleanup(cp, error);
      return;
    }
  } else if (cp->PipeSharedSTDIN) {
    /* Share this process's stdin with the child.  */
    kwsysProcessSetupSharedPipe(STD_INPUT_HANDLE, &cp->PipeChildStd[0]);
  } else if (cp->PipeNativeSTDIN[0]) {
    /* Use the provided native pipe.  */
    kwsysProcessSetupPipeNative(cp->PipeNativeSTDIN[0], &cp->PipeChildStd[0]);
  } else {
    /* Explicitly give the child no stdin.  */
    cp->PipeChildStd[0] = INVALID_HANDLE_VALUE;
  }