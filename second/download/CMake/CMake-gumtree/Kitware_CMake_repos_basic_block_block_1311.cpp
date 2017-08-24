(!(cp->Pipe[i].Reader.Thread = CreateThread(
            0, 1024, kwsysProcessPipeThreadRead, &cp->Pipe[i], 0, &dummy))) {
      kwsysProcess_Delete(cp);
      return 0;
    }