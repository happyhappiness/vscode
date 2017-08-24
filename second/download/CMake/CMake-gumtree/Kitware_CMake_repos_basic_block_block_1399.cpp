{
  kwsysProcessTime userStartTime;
  kwsysProcessTime timeoutLength;
  kwsysProcessTime timeoutTime;
  DWORD timeout;
  int user;
  int done = 0;
  int expired = 0;
  int pipeId = kwsysProcess_Pipe_None;
  DWORD w;

  /* Make sure we are executing a process.  */
  if (!cp || cp->State != kwsysProcess_State_Executing || cp->Killed ||
      cp->TimeoutExpired) {
    return kwsysProcess_Pipe_None;
  }

  /* Record the time at which user timeout period starts.  */
  userStartTime = kwsysProcessTimeGetCurrent();

  /* Calculate the time at which a timeout will expire, and whether it
     is the user or process timeout.  */
  user = kwsysProcessGetTimeoutTime(cp, userTimeout, &timeoutTime);

  /* Loop until we have a reason to return.  */
  while (!done && cp->PipesLeft > 0) {
    /* If we previously got data from a thread, let it know we are
       done with the data.  */
    if (cp->CurrentIndex < KWSYSPE_PIPE_COUNT) {
      KWSYSPE_DEBUG((stderr, "releasing reader %d\n", cp->CurrentIndex));
      ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Reader.Go, 1, 0);
      cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
    }

    /* Setup a timeout if required.  */
    if (kwsysProcessGetTimeoutLeft(&timeoutTime, user ? userTimeout : 0,
                                   &timeoutLength)) {
      /* Timeout has already expired.  */
      expired = 1;
      break;
    }
    if (timeoutTime.QuadPart < 0) {
      timeout = INFINITE;
    } else {
      timeout = kwsysProcessTimeToDWORD(timeoutLength);
    }

    /* Wait for a pipe's thread to signal or a process to terminate.  */
    w = WaitForMultipleObjects(cp->ProcessEventsLength, cp->ProcessEvents, 0,
                               timeout);
    if (w == WAIT_TIMEOUT) {
      /* Timeout has expired.  */
      expired = 1;
      done = 1;
    } else if (w == WAIT_OBJECT_0) {
      /* Save the index of the reporting thread and release the mutex.
         The thread will block until we signal its Empty mutex.  */
      cp->CurrentIndex = cp->SharedIndex;
      ReleaseSemaphore(cp->SharedIndexMutex, 1, 0);

      /* Data are available or a pipe closed.  */
      if (cp->Pipe[cp->CurrentIndex].Closed) {
        /* The pipe closed at the write end.  Close the read end and
           inform the wakeup thread it is done with this process.  */
        kwsysProcessCleanupHandle(&cp->Pipe[cp->CurrentIndex].Read);
        ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Waker.Go, 1, 0);
        KWSYSPE_DEBUG((stderr, "wakeup %d\n", cp->CurrentIndex));
        --cp->PipesLeft;
      } else if (data && length) {
        /* Report this data.  */
        *data = cp->Pipe[cp->CurrentIndex].DataBuffer;
        *length = cp->Pipe[cp->CurrentIndex].DataLength;
        switch (cp->CurrentIndex) {
          case KWSYSPE_PIPE_STDOUT:
            pipeId = kwsysProcess_Pipe_STDOUT;
            break;
          case KWSYSPE_PIPE_STDERR:
            pipeId = kwsysProcess_Pipe_STDERR;
            break;
        }
        done = 1;
      }
    } else {
      /* A process has terminated.  */
      kwsysProcessDestroy(cp, w - WAIT_OBJECT_0);
    }
  }

  /* Update the user timeout.  */
  if (userTimeout) {
    kwsysProcessTime userEndTime = kwsysProcessTimeGetCurrent();
    kwsysProcessTime difference =
      kwsysProcessTimeSubtract(userEndTime, userStartTime);
    double d = kwsysProcessTimeToDouble(difference);
    *userTimeout -= d;
    if (*userTimeout < 0) {
      *userTimeout = 0;
    }
  }

  /* Check what happened.  */
  if (pipeId) {
    /* Data are ready on a pipe.  */
    return pipeId;
  } else if (expired) {
    /* A timeout has expired.  */
    if (user) {
      /* The user timeout has expired.  It has no time left.  */
      return kwsysProcess_Pipe_Timeout;
    } else {
      /* The process timeout has expired.  Kill the child now.  */
      KWSYSPE_DEBUG((stderr, "killing child because timeout expired\n"));
      kwsysProcess_Kill(cp);
      cp->TimeoutExpired = 1;
      cp->Killed = 0;
      return kwsysProcess_Pipe_None;
    }
  } else {
    /* The children have terminated and no more data are available.  */
    return kwsysProcess_Pipe_None;
  }
}