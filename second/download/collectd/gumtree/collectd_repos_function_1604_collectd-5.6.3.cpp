static int statsd_init(void) /* {{{ */
{
  pthread_mutex_lock(&metrics_lock);
  if (metrics_tree == NULL)
    metrics_tree = c_avl_create((int (*)(const void *, const void *))strcmp);

  if (!network_thread_running) {
    int status;

    status = pthread_create(&network_thread,
                            /* attr = */ NULL, statsd_network_thread,
                            /* args = */ NULL);
    if (status != 0) {
      char errbuf[1024];
      pthread_mutex_unlock(&metrics_lock);
      ERROR("statsd plugin: pthread_create failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return (status);
    }
  }
  network_thread_running = 1;

  pthread_mutex_unlock(&metrics_lock);

  return (0);
}