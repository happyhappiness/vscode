static
void release_thread_sync(struct thread_sync_data * tsd)
{
  ReleaseMutex(tsd->mutex_terminate);
}