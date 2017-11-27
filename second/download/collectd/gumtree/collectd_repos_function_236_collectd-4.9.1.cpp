static int stop_thread (void) /* {{{ */
{
  int status;

  pthread_mutex_lock (&ping_lock);

  if (ping_thread_loop == 0)
  {
    pthread_mutex_unlock (&ping_lock);
    return (-1);
  }

  ping_thread_loop = 0;
  pthread_cond_broadcast (&ping_cond);
  pthread_mutex_unlock (&ping_lock);

  status = pthread_join (ping_thread_id, /* return = */ NULL);
  if (status != 0)
  {
    ERROR ("ping plugin: Stopping thread failed.");
    status = -1;
  }

  memset (&ping_thread_id, 0, sizeof (ping_thread_id));
  ping_thread_error = 0;

  return (status);
}