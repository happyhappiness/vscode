(cp->Pipe[i].Waker.Thread) {
      /* Signal the thread we are ready for it.  It will terminate
         immediately since Deleting is set.  */
      ReleaseSemaphore(cp->Pipe[i].Waker.Ready, 1, 0);

      /* Wait for the thread to exit.  */
      WaitForSingleObject(cp->Pipe[i].Waker.Thread, INFINITE);

      /* Close the handle to the thread. */
      kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Thread);
    }