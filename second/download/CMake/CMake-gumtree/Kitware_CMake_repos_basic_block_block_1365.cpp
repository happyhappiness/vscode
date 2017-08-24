{
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