BOOL acquire_thread_sync(struct thread_sync_data * tsd)
{
  /* is the thread initiator still waiting for us ? */
  if (WaitForSingleObject(tsd->mutex_waiting, 0) == WAIT_TIMEOUT) {
    /* yes, it is */

    /* Waiting access to event_terminate */
    if (WaitForSingleObject(tsd->mutex_terminate, INFINITE) != WAIT_OBJECT_0) {
      /* Something went wrong - now just ignoring */
    }
    else {
      if (WaitForSingleObject(tsd->event_terminate, 0) != WAIT_TIMEOUT) {
        /* Parent thread signaled us to terminate.
         * This means that all data in conn->async is now destroyed
         * and we cannot use it.
         */
      }
      else {
        return TRUE;
      }
    }
  }
  return FALSE;
}