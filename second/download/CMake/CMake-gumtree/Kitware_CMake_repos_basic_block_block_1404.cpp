{
    KWSYSPE_DEBUG((stderr, "waiting reader reset %d\n", i));
    WaitForSingleObject(cp->Pipe[i].Reader.Reset, INFINITE);
    KWSYSPE_DEBUG((stderr, "waiting waker reset %d\n", i));
    WaitForSingleObject(cp->Pipe[i].Waker.Reset, INFINITE);
  }