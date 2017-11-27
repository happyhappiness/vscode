int uc_check_timeout(void) {
  struct {
    char *key;
    cdtime_t time;
    cdtime_t interval;
  } *expired = NULL;
  size_t expired_num = 0;

  pthread_mutex_lock(&cache_lock);
  cdtime_t now = cdtime();

  /* Build a list of entries to be flushed */
  c_avl_iterator_t *iter = c_avl_get_iterator(cache_tree);
  char *key = NULL;
  cache_entry_t *ce = NULL;
  while (c_avl_iterator_next(iter, (void *)&key, (void *)&ce) == 0) {
    /* If the entry is fresh enough, continue. */
    if ((now - ce->last_update) < (ce->interval * timeout_g))
      continue;

    void *tmp = realloc(expired, (expired_num + 1) * sizeof(*expired));
    if (tmp == NULL) {
      ERROR("uc_check_timeout: realloc failed.");
      continue;
    }
    expired = tmp;

    expired[expired_num].key = strdup(key);
    expired[expired_num].time = ce->last_time;
    expired[expired_num].interval = ce->interval;

    if (expired[expired_num].key == NULL) {
      ERROR("uc_check_timeout: strdup failed.");
      continue;
    }

    expired_num++;
  } /* while (c_avl_iterator_next) */

  c_avl_iterator_destroy(iter);
  pthread_mutex_unlock(&cache_lock);

  if (expired_num == 0) {
    sfree(expired);
    return 0;
  }

  /* Call the "missing" callback for each value. Do this before removing the
   * value from the cache, so that callbacks can still access the data stored,
   * including plugin specific meta data, rates, history, …. This must be done
   * without holding the lock, otherwise we will run into a deadlock if a
   * plugin calls the cache interface. */
  for (size_t i = 0; i < expired_num; i++) {
    value_list_t vl = {
        .time = expired[i].time, .interval = expired[i].interval,
    };

    if (parse_identifier_vl(expired[i].key, &vl) != 0) {
      ERROR("uc_check_timeout: parse_identifier_vl (\"%s\") failed.",
            expired[i].key);
      continue;
    }

    plugin_dispatch_missing(&vl);
  } /* for (i = 0; i < expired_num; i++) */

  /* Now actually remove all the values from the cache. We don't re-evaluate
   * the timestamp again, so in theory it is possible we remove a value after
   * it is updated here. */
  pthread_mutex_lock(&cache_lock);
  for (size_t i = 0; i < expired_num; i++) {
    char *key = NULL;
    cache_entry_t *value = NULL;

    if (c_avl_remove(cache_tree, expired[i].key, (void *)&key,
                     (void *)&value) != 0) {
      ERROR("uc_check_timeout: c_avl_remove (\"%s\") failed.", expired[i].key);
      sfree(expired[i].key);
      continue;
    }
    sfree(key);
    cache_free(value);

    sfree(expired[i].key);
  } /* for (i = 0; i < expired_num; i++) */
  pthread_mutex_unlock(&cache_lock);

  sfree(expired);
  return 0;
}