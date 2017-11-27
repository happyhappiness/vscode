static int rrd_cache_destroy (void) /* {{{ */
{
  void *key = NULL;
  void *value = NULL;

  int non_empty = 0;

  pthread_mutex_lock (&cache_lock);

  if (cache == NULL)
  {
    pthread_mutex_unlock (&cache_lock);
    return (0);
  }

  while (c_avl_pick (cache, &key, &value) == 0)
  {
    rrd_cache_t *rc;
    int i;

    sfree (key);
    key = NULL;

    rc = value;
    value = NULL;

    if (rc->values_num > 0)
      non_empty++;

    for (i = 0; i < rc->values_num; i++)
      sfree (rc->values[i]);
    sfree (rc->values);
    sfree (rc);
  }

  c_avl_destroy (cache);
  cache = NULL;

  if (non_empty > 0)
  {
    INFO ("rrdtool plugin: %i cache %s had values when destroying the cache.",
        non_empty, (non_empty == 1) ? "entry" : "entries");
  }
  else
  {
    DEBUG ("rrdtool plugin: No values have been lost "
        "when destroying the cache.");
  }

  pthread_mutex_unlock (&cache_lock);
  return (0);
}