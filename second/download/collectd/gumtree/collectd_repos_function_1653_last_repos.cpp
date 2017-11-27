static int rrd_cache_insert(const char *filename, const char *value,
                            cdtime_t value_time) {
  rrd_cache_t *rc = NULL;
  int new_rc = 0;
  char **values_new;

  pthread_mutex_lock(&cache_lock);

  /* This shouldn't happen, but it did happen at least once, so we'll be
   * careful. */
  if (cache == NULL) {
    pthread_mutex_unlock(&cache_lock);
    WARNING("rrdtool plugin: cache == NULL.");
    return -1;
  }

  c_avl_get(cache, filename, (void *)&rc);

  if (rc == NULL) {
    rc = malloc(sizeof(*rc));
    if (rc == NULL) {
      pthread_mutex_unlock(&cache_lock);
      return -1;
    }
    rc->values_num = 0;
    rc->values = NULL;
    rc->first_value = 0;
    rc->last_value = 0;
    rc->random_variation = rrd_get_random_variation();
    rc->flags = FLAG_NONE;
    new_rc = 1;
  }

  assert(value_time > 0); /* plugin_dispatch() ensures this. */
  if (rc->last_value >= value_time) {
    pthread_mutex_unlock(&cache_lock);
    DEBUG("rrdtool plugin: (rc->last_value = %" PRIu64 ") "
          ">= (value_time = %" PRIu64 ")",
          rc->last_value, value_time);
    return -1;
  }

  values_new =
      realloc((void *)rc->values, (rc->values_num + 1) * sizeof(char *));
  if (values_new == NULL) {
    char errbuf[1024];
    void *cache_key = NULL;

    sstrerror(errno, errbuf, sizeof(errbuf));

    c_avl_remove(cache, filename, &cache_key, NULL);
    pthread_mutex_unlock(&cache_lock);

    ERROR("rrdtool plugin: realloc failed: %s", errbuf);

    sfree(cache_key);
    sfree(rc->values);
    sfree(rc);
    return -1;
  }
  rc->values = values_new;

  rc->values[rc->values_num] = strdup(value);
  if (rc->values[rc->values_num] != NULL)
    rc->values_num++;

  if (rc->values_num == 1)
    rc->first_value = value_time;
  rc->last_value = value_time;

  /* Insert if this is the first value */
  if (new_rc == 1) {
    void *cache_key = strdup(filename);

    if (cache_key == NULL) {
      char errbuf[1024];
      sstrerror(errno, errbuf, sizeof(errbuf));

      pthread_mutex_unlock(&cache_lock);

      ERROR("rrdtool plugin: strdup failed: %s", errbuf);

      sfree(rc->values[0]);
      sfree(rc->values);
      sfree(rc);
      return -1;
    }

    c_avl_insert(cache, cache_key, rc);
  }

  DEBUG("rrdtool plugin: rrd_cache_insert: file = %s; "
        "values_num = %i; age = %.3f;",
        filename, rc->values_num,
        CDTIME_T_TO_DOUBLE(rc->last_value - rc->first_value));

  if ((rc->last_value - rc->first_value) >=
      (cache_timeout + rc->random_variation)) {
    /* XXX: If you need to lock both, cache_lock and queue_lock, at
     * the same time, ALWAYS lock `cache_lock' first! */
    if (rc->flags == FLAG_NONE) {
      int status;

      status = rrd_queue_enqueue(filename, &queue_head, &queue_tail);
      if (status == 0)
        rc->flags = FLAG_QUEUED;

      rc->random_variation = rrd_get_random_variation();
    } else {
      DEBUG("rrdtool plugin: `%s' is already queued.", filename);
    }
  }

  if ((cache_timeout > 0) &&
      ((cdtime() - cache_flush_last) > cache_flush_timeout))
    rrd_cache_flush(cache_timeout + random_timeout);

  pthread_mutex_unlock(&cache_lock);

  return 0;
}