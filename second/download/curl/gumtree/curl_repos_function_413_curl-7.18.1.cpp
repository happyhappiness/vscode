static
void destroy_thread_sync_data(struct thread_sync_data * tsd)
{
  if(tsd->hostname)
    free(tsd->hostname);
  if(tsd->event_terminate)
    CloseHandle(tsd->event_terminate);
  if(tsd->mutex_terminate)
    CloseHandle(tsd->mutex_terminate);
  if(tsd->mutex_waiting)
    CloseHandle(tsd->mutex_waiting);
  memset(tsd,0,sizeof(*tsd));
}