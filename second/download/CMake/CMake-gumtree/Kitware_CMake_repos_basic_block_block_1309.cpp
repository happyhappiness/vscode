(!(cp->Pipe[i].Waker.Reset = CreateSemaphore(0, 0, 1, 0))) {
      kwsysProcess_Delete(cp);
      return 0;
    }