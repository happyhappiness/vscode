{
    ReleaseSemaphore(cp->Pipe[i].Reader.Ready, 1, 0);
    ReleaseSemaphore(cp->Pipe[i].Waker.Ready, 1, 0);
  }