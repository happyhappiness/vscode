void destroy_thread_sync_data(struct thread_sync_data * tsd)
{
  if (tsd->hostname) {
    free(tsd->hostname);
    tsd->hostname = NULL;
  }
  if (tsd->event_terminate) {
    CloseHandle(tsd->event_terminate);
    tsd->event_terminate = NULL;
  }
  if (tsd->mutex_terminate) {
    CloseHandle(tsd->mutex_terminate);
    tsd->mutex_terminate = NULL;
  }
  if (tsd->mutex_waiting) {
    CloseHandle(tsd->mutex_waiting);
    tsd->mutex_waiting = NULL;
  }
}