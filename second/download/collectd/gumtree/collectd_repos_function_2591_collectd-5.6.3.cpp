static void start_write_threads(size_t num) /* {{{ */
{
  if (write_threads != NULL)
    return;

  write_threads = (pthread_t *)calloc(num, sizeof(pthread_t));
  if (write_threads == NULL) {
    ERROR("plugin: start_write_threads: calloc failed.");
    return;
  }

  write_threads_num = 0;
  for (size_t i = 0; i < num; i++) {
    int status;

    status = pthread_create(write_threads + write_threads_num,
                            /* attr = */ NULL, plugin_write_thread,
                            /* arg = */ NULL);
    if (status != 0) {
      char errbuf[1024];
      ERROR("plugin: start_write_threads: pthread_create failed "
            "with status %i (%s).",
            status, sstrerror(status, errbuf, sizeof(errbuf)));
      return;
    }

    write_threads_num++;
  } /* for (i) */
}