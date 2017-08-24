{
    WaitForSingleObject(cp->Pipe[i].Reader.Reset, INFINITE);
    WaitForSingleObject(cp->Pipe[i].Waker.Reset, INFINITE);
  }