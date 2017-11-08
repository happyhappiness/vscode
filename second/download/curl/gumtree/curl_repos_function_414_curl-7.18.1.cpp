static
BOOL init_thread_sync_data(struct thread_data * td,
                           const char * hostname,
                           struct thread_sync_data * tsd)
{
  HANDLE curr_proc = GetCurrentProcess();

  memset(tsd, 0, sizeof(*tsd));
  if(!DuplicateHandle(curr_proc, td->mutex_waiting,
                       curr_proc, &tsd->mutex_waiting, 0, FALSE,
                       DUPLICATE_SAME_ACCESS)) {
    /* failed to duplicate the mutex, no point in continuing */
    destroy_thread_sync_data(tsd);
    return FALSE;
  }
  if(!DuplicateHandle(curr_proc, td->mutex_terminate,
                       curr_proc, &tsd->mutex_terminate, 0, FALSE,
                       DUPLICATE_SAME_ACCESS)) {
    /* failed to duplicate the mutex, no point in continuing */
    destroy_thread_sync_data(tsd);
    return FALSE;
  }
  if(!DuplicateHandle(curr_proc, td->event_terminate,
                       curr_proc, &tsd->event_terminate, 0, FALSE,
                       DUPLICATE_SAME_ACCESS)) {
    /* failed to duplicate the event, no point in continuing */
    destroy_thread_sync_data(tsd);
    return FALSE;
  }
  /* Copying hostname string because original can be destroyed by parent
   * thread during gethostbyname execution.
   */
  tsd->hostname = strdup(hostname);
  if(!tsd->hostname) {
    /* Memory allocation failed */
    destroy_thread_sync_data(tsd);
    return FALSE;
  }
  return TRUE;
}