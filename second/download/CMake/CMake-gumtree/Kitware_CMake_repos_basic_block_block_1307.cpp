(!(cp->Pipe[i].Waker.Thread = CreateThread(
            0, 1024, kwsysProcessPipeThreadWake, &cp->Pipe[i], 0, &dummy))) {
      kwsysProcess_Delete(cp);
      return 0;
    }