static int rrd_init(void) {
  static int init_once = 0;
  int status;

  if (init_once != 0)
    return (0);
  init_once = 1;

  if (rrdcreate_config.heartbeat <= 0)
    rrdcreate_config.heartbeat = 2 * rrdcreate_config.stepsize;

  /* Set the cache up */
  pthread_mutex_lock(&cache_lock);

  cache = c_avl_create((int (*)(const void *, const void *))strcmp);
  if (cache == NULL) {
    pthread_mutex_unlock(&cache_lock);
    ERROR("rrdtool plugin: c_avl_create failed.");
    return (-1);
  }

  cache_flush_last = cdtime();
  if (cache_timeout == 0) {
    cache_flush_timeout = 0;
  } else if (cache_flush_timeout < cache_timeout)
    cache_flush_timeout = 10 * cache_timeout;

  pthread_mutex_unlock(&cache_lock);

  status =
      plugin_thread_create(&queue_thread, /* attr = */ NULL, rrd_queue_thread,
                           /* args = */ NULL, "rrdtool queue");
  if (status != 0) {
    ERROR("rrdtool plugin: Cannot create queue-thread.");
    return (-1);
  }
  queue_thread_running = 1;

  DEBUG("rrdtool plugin: rrd_init: datadir = %s; stepsize = %lu;"
        " heartbeat = %i; rrarows = %i; xff = %lf;",
        (datadir == NULL) ? "(null)" : datadir, rrdcreate_config.stepsize,
        rrdcreate_config.heartbeat, rrdcreate_config.rrarows,
        rrdcreate_config.xff);

  return (0);
}