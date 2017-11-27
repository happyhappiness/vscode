static int start_thread(void) /* {{{ */
{
  int status;

  pthread_mutex_lock(&ping_lock);

  if (ping_thread_loop != 0) {
    pthread_mutex_unlock(&ping_lock);
    return (0);
  }

  ping_thread_loop = 1;
  ping_thread_error = 0;
  status = plugin_thread_create(&ping_thread_id, /* attr = */ NULL, ping_thread,
                                /* arg = */ (void *)0);
  if (status != 0) {
    ping_thread_loop = 0;
    ERROR("ping plugin: Starting thread failed.");
    pthread_mutex_unlock(&ping_lock);
    return (-1);
  }

  pthread_mutex_unlock(&ping_lock);
  return (0);
}