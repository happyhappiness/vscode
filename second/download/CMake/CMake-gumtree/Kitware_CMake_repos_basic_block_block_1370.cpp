{
    /* Child startup control data.  */
    kwsysProcessCreateInformation si;
    HANDLE nextStdInput = cp->PipeChildStd[0];

    /* Initialize startup info data.  */
    ZeroMemory(&si, sizeof(si));
    si.StartupInfo.cb = sizeof(si.StartupInfo);

    /* Decide whether a child window should be shown.  */
    si.StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
    si.StartupInfo.wShowWindow =
      (unsigned short)(cp->HideWindow ? SW_HIDE : SW_SHOWDEFAULT);

    /* Connect the child's output pipes to the threads.  */
    si.StartupInfo.dwFlags |= STARTF_USESTDHANDLES;

    for (i = 0; i < cp->NumberOfCommands; ++i) {
      /* Setup the process's pipes.  */
      si.hStdInput = nextStdInput;
      if (i == cp->NumberOfCommands - 1) {
        /* The last child gets the overall stdout.  */
        nextStdInput = INVALID_HANDLE_VALUE;
        si.hStdOutput = cp->PipeChildStd[1];
      } else {
        /* Create a pipe to sit between the children.  */
        HANDLE p[2] = { INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE };
        if (!CreatePipe(&p[0], &p[1], 0, 0)) {
          DWORD error = GetLastError();
          if (nextStdInput != cp->PipeChildStd[0]) {
            kwsysProcessCleanupHandle(&nextStdInput);
          }
          kwsysProcessCleanup(cp, error);
          return;
        }
        nextStdInput = p[0];
        si.hStdOutput = p[1];
      }
      si.hStdError =
        cp->MergeOutput ? cp->PipeChildStd[1] : cp->PipeChildStd[2];

      {
        DWORD error = kwsysProcessCreate(cp, i, &si);

        /* Close our copies of pipes used between children.  */
        if (si.hStdInput != cp->PipeChildStd[0]) {
          kwsysProcessCleanupHandle(&si.hStdInput);
        }
        if (si.hStdOutput != cp->PipeChildStd[1]) {
          kwsysProcessCleanupHandle(&si.hStdOutput);
        }
        if (si.hStdError != cp->PipeChildStd[2] && !cp->MergeOutput) {
          kwsysProcessCleanupHandle(&si.hStdError);
        }
        if (!error) {
          cp->ProcessEvents[i + 1] = cp->ProcessInformation[i].hProcess;
        } else {
          if (nextStdInput != cp->PipeChildStd[0]) {
            kwsysProcessCleanupHandle(&nextStdInput);
          }
          kwsysProcessCleanup(cp, error);
          return;
        }
      }
    }
  }