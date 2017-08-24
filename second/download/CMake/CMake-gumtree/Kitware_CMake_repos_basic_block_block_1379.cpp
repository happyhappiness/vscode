(cp->PipeChildStd[0] == INVALID_HANDLE_VALUE) {
      kwsysProcessCleanup(cp, error);
      return;
    }