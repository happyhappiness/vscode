static void start_read_threads(int num) {
  if (read_threads != NULL)
    return;

  read_threads = (pthread_t *)calloc(num, sizeof(pthread_t));
  if (read_threads == NULL) {
    ERROR("plugin: start_read_threads: calloc failed.");
    return;
  }

  read_threads_num = 0;
  for (int i = 0; i < num; i++) {
    if (pthread_create(read_threads + read_threads_num, NULL,
                       plugin_read_thread, NULL) == 0) {
      read_threads_num++;
    } else {
      ERROR("plugin: start_read_threads: pthread_create failed.");
      return;
    }
  } /* for (i) */
}