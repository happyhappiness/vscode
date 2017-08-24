{
    DWORD dummy = 0;

    /* Assign the thread its index.  */
    cp->Pipe[i].Index = i;

    /* Give the thread a pointer back to the kwsysProcess instance.  */
    cp->Pipe[i].Process = cp;

    /* No process is yet running.  Initialize semaphore to 0.  */
    if (!(cp->Pipe[i].Reader.Ready = CreateSemaphore(0, 0, 1, 0))) {
      kwsysProcess_Delete(cp);
      return 0;
    }

    /* The pipe is not yet reset.  Initialize semaphore to 0.  */
    if (!(cp->Pipe[i].Reader.Reset = CreateSemaphore(0, 0, 1, 0))) {
      kwsysProcess_Delete(cp);
      return 0;
    }

    /* The thread's buffer is initially empty.  Initialize semaphore to 1.  */
    if (!(cp->Pipe[i].Reader.Go = CreateSemaphore(0, 1, 1, 0))) {
      kwsysProcess_Delete(cp);
      return 0;
    }

    /* Create the reading thread.  It will block immediately.  The
       thread will not make deeply nested calls, so we need only a
       small stack.  */
    if (!(cp->Pipe[i].Reader.Thread = CreateThread(
            0, 1024, kwsysProcessPipeThreadRead, &cp->Pipe[i], 0, &dummy))) {
      kwsysProcess_Delete(cp);
      return 0;
    }

    /* No process is yet running.  Initialize semaphore to 0.  */
    if (!(cp->Pipe[i].Waker.Ready = CreateSemaphore(0, 0, 1, 0))) {
      kwsysProcess_Delete(cp);
      return 0;
    }

    /* The pipe is not yet reset.  Initialize semaphore to 0.  */
    if (!(cp->Pipe[i].Waker.Reset = CreateSemaphore(0, 0, 1, 0))) {
      kwsysProcess_Delete(cp);
      return 0;
    }

    /* The waker should not wake immediately.  Initialize semaphore to 0.  */
    if (!(cp->Pipe[i].Waker.Go = CreateSemaphore(0, 0, 1, 0))) {
      kwsysProcess_Delete(cp);
      return 0;
    }

    /* Create the waking thread.  It will block immediately.  The
       thread will not make deeply nested calls, so we need only a
       small stack.  */
    if (!(cp->Pipe[i].Waker.Thread = CreateThread(
            0, 1024, kwsysProcessPipeThreadWake, &cp->Pipe[i], 0, &dummy))) {
      kwsysProcess_Delete(cp);
      return 0;
    }
  }