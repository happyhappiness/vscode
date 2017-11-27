static void start_read_threads(size_t num) /* {{{ */
{
  if (read_threads != NULL)
    return;

  read_threads = (pthread_t *)calloc(num, sizeof(pthread_t));
  if (read_threads == NULL) {
    ERROR("plugin: start_read_threads: calloc failed.");
    return;
  }

  read_threads_num = 0;
  for (size_t i = 0; i < num; i++) {
    int status = pthread_create(read_threads + read_threads_num,
                                /* attr = */ NULL, plugin_read_thread,
                                /* arg = */ NULL);
    if (status != 0) {
      char errbuf[1024];
      ERROR("plugin: start_read_threads: pthread_create failed "
            "with status %i (%s).",
            status, sstrerror(status, errbuf, sizeof(errbuf)));
      return;
    }

    char name[THREAD_NAME_MAX];
    ssnprintf(name, sizeof(name), "reader#%zu", read_threads_num);
    set_thread_name(read_threads[read_threads_num], name);

    read_threads_num++;
  } /* for (i) */
}