{
          DWORD error = GetLastError();
          if (nextStdInput != cp->PipeChildStd[0]) {
            kwsysProcessCleanupHandle(&nextStdInput);
          }
          kwsysProcessCleanup(cp, error);
          return;
        }