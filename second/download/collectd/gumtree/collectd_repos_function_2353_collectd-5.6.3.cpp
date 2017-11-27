int uc_check_timeout(void) {
  cdtime_t now;
  cache_entry_t *ce;

  char **keys = NULL;
  cdtime_t *keys_time = NULL;
  cdtime_t *keys_interval = NULL;
  int keys_len = 0;

  char *key;
  c_avl_iterator_t *iter;

  int status;

  pthread_mutex_lock(&cache_lock);

  now = cdtime();

  /* Build a list of entries to be flushed */
  iter = c_avl_get_iterator(cache_tree);
  while (c_avl_iterator_next(iter, (void *)&key, (void *)&ce) == 0) {
    char **tmp;
    cdtime_t *tmp_time;

    /* If the entry is fresh enough, continue. */
    if ((now - ce->last_update) < (ce->interval * timeout_g))
      continue;

    /* If entry has not been updated, add to `keys' array */
    tmp = realloc((void *)keys, (keys_len + 1) * sizeof(char *));
    if (tmp == NULL) {
      ERROR("uc_check_timeout: realloc failed.");
      continue;
    }
    keys = tmp;

    tmp_time = realloc(keys_time, (keys_len + 1) * sizeof(*keys_time));
    if (tmp_time == NULL) {
      ERROR("uc_check_timeout: realloc failed.");
      continue;
    }
    keys_time = tmp_time;

    tmp_time = realloc(keys_interval, (keys_len + 1) * sizeof(*keys_interval));
    if (tmp_time == NULL) {
      ERROR("uc_check_timeout: realloc failed.");
      continue;
    }
    keys_interval = tmp_time;

    keys[keys_len] = strdup(key);
    if (keys[keys_len] == NULL) {
      ERROR("uc_check_timeout: strdup failed.");
      continue;
    }
    keys_time[keys_len] = ce->last_time;
    keys_interval[keys_len] = ce->interval;

    keys_len++;
  } /* while (c_avl_iterator_next) */

  c_avl_iterator_destroy(iter);
  pthread_mutex_unlock(&cache_lock);

  if (keys_len == 0) {
    /* realloc() may have been called for these. */
    sfree(keys);
    sfree(keys_time);
    sfree(keys_interval);
    return (0);
  }

  /* Call the "missing" callback for each value. Do this before removing the
   * value from the cache, so that callbacks can still access the data stored,
   * including plugin specific meta data, rates, history, …. This must be done
   * without holding the lock, otherwise we will run into a deadlock if a
   * plugin calls the cache interface. */
  for (int i = 0; i < keys_len; i++) {
    value_list_t vl = VALUE_LIST_INIT;

    vl.values = NULL;
    vl.values_len = 0;
    vl.meta = NULL;

    status = parse_identifier_vl(keys[i], &vl);
    if (status != 0) {
      ERROR("uc_check_timeout: parse_identifier_vl (\"%s\") failed.", keys[i]);
      continue;
    }

    vl.time = keys_time[i];
    vl.interval = keys_interval[i];

    plugin_dispatch_missing(&vl);
  } /* for (i = 0; i < keys_len; i++) */

  /* Now actually remove all the values from the cache. We don't re-evaluate
   * the timestamp again, so in theory it is possible we remove a value after
   * it is updated here. */
  pthread_mutex_lock(&cache_lock);
  for (int i = 0; i < keys_len; i++) {
    key = NULL;
    ce = NULL;

    status = c_avl_remove(cache_tree, keys[i], (void *)&key, (void *)&ce);
    if (status != 0) {
      ERROR("uc_check_timeout: c_avl_remove (\"%s\") failed.", keys[i]);
      sfree(keys[i]);
      continue;
    }

    sfree(keys[i]);
    sfree(key);
    cache_free(ce);
  } /* for (i = 0; i < keys_len; i++) */
  pthread_mutex_unlock(&cache_lock);

  sfree(keys);
  sfree(keys_time);
  sfree(keys_interval);

  return (0);
}