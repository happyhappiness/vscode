{
      KWSYSPE_DEBUG((stderr, "releasing waker %d\n", i));
      ReleaseSemaphore(cp->Pipe[i].Waker.Go, 1, 0);
    }