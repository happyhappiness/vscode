static void stop_read_threads(void) {
  if (read_threads == NULL)
    return;

  INFO("collectd: Stopping %zu read threads.", read_threads_num);

  pthread_mutex_lock(&read_lock);
  read_loop = 0;
  DEBUG("plugin: stop_read_threads: Signalling `read_cond'");
  pthread_cond_broadcast(&read_cond);
  pthread_mutex_unlock(&read_lock);

  for (size_t i = 0; i < read_threads_num; i++) {
    if (pthread_join(read_threads[i], NULL) != 0) {
      ERROR("plugin: stop_read_threads: pthread_join failed.");
    }
    read_threads[i] = (pthread_t)0;
  }
  sfree(read_threads);
  read_threads_num = 0;
}