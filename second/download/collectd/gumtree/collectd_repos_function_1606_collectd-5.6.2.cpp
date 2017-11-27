static int statsd_shutdown(void) /* {{{ */
{
  void *key;
  void *value;

  if (network_thread_running) {
    network_thread_shutdown = 1;
    pthread_kill(network_thread, SIGTERM);
    pthread_join(network_thread, /* retval = */ NULL);
  }
  network_thread_running = 0;

  pthread_mutex_lock(&metrics_lock);

  while (c_avl_pick(metrics_tree, &key, &value) == 0) {
    sfree(key);
    statsd_metric_free(value);
  }
  c_avl_destroy(metrics_tree);
  metrics_tree = NULL;

  sfree(conf_node);
  sfree(conf_service);

  pthread_mutex_unlock(&metrics_lock);

  return (0);
}