{
  int i;

  /* Make sure we have an instance.  */
  if (!cp) {
    return;
  }

  /* If the process is executing, wait for it to finish.  */
  if (cp->State == kwsysProcess_State_Executing) {
    if (cp->Detached) {
      kwsysProcess_Disown(cp);
    } else {
      kwsysProcess_WaitForExit(cp, 0);
    }
  }

  /* We are deleting the kwsysProcess instance.  */
  cp->Deleting = 1;

  /* Terminate each of the threads.  */
  for (i = 0; i < KWSYSPE_PIPE_COUNT; ++i) {
    /* Terminate this reading thread.  */
    if (cp->Pipe[i].Reader.Thread) {
      /* Signal the thread we are ready for it.  It will terminate
         immediately since Deleting is set.  */
      ReleaseSemaphore(cp->Pipe[i].Reader.Ready, 1, 0);

      /* Wait for the thread to exit.  */
      WaitForSingleObject(cp->Pipe[i].Reader.Thread, INFINITE);

      /* Close the handle to the thread. */
      kwsysProcessCleanupHandle(&cp->Pipe[i].Reader.Thread);
    }

    /* Terminate this waking thread.  */
    if (cp->Pipe[i].Waker.Thread) {
      /* Signal the thread we are ready for it.  It will terminate
         immediately since Deleting is set.  */
      ReleaseSemaphore(cp->Pipe[i].Waker.Ready, 1, 0);

      /* Wait for the thread to exit.  */
      WaitForSingleObject(cp->Pipe[i].Waker.Thread, INFINITE);

      /* Close the handle to the thread. */
      kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Thread);
    }

    /* Cleanup the pipe's semaphores.  */
    kwsysProcessCleanupHandle(&cp->Pipe[i].Reader.Ready);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Reader.Go);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Reader.Reset);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Ready);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Go);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Reset);
  }

  /* Close the shared semaphores.  */
  kwsysProcessCleanupHandle(&cp->SharedIndexMutex);
  kwsysProcessCleanupHandle(&cp->Full);

  /* Free memory.  */
  kwsysProcess_SetCommand(cp, 0);
  kwsysProcess_SetWorkingDirectory(cp, 0);
  kwsysProcess_SetPipeFile(cp, kwsysProcess_Pipe_STDIN, 0);
  kwsysProcess_SetPipeFile(cp, kwsysProcess_Pipe_STDOUT, 0);
  kwsysProcess_SetPipeFile(cp, kwsysProcess_Pipe_STDERR, 0);
  if (cp->CommandExitCodes) {
    free(cp->CommandExitCodes);
  }
  free(cp->ProcessResults);
  free(cp);
}