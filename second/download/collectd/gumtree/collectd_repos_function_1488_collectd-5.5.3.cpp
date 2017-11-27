static int statsd_handle_set (char const *name, /* {{{ */
    char const *set_key_orig)
{
  statsd_metric_t *metric = NULL;
  char *set_key;
  int status;

  pthread_mutex_lock (&metrics_lock);

  metric = statsd_metric_lookup_unsafe (name, STATSD_SET);
  if (metric == NULL)
  {
    pthread_mutex_unlock (&metrics_lock);
    return (-1);
  }

  /* Make sure metric->set exists. */
  if (metric->set == NULL)
    metric->set = c_avl_create ((void *) strcmp);

  if (metric->set == NULL)
  {
    pthread_mutex_unlock (&metrics_lock);
    ERROR ("statsd plugin: c_avl_create failed.");
    return (-1);
  }

  set_key = strdup (set_key_orig);
  if (set_key == NULL)
  {
    pthread_mutex_unlock (&metrics_lock);
    ERROR ("statsd plugin: strdup failed.");
    return (-1);
  }

  status = c_avl_insert (metric->set, set_key, /* value = */ NULL);
  if (status < 0)
  {
    pthread_mutex_unlock (&metrics_lock);
    if (status < 0)
      ERROR ("statsd plugin: c_avl_insert (\"%s\") failed with status %i.",
          set_key, status);
    sfree (set_key);
    return (-1);
  }
  else if (status > 0) /* key already exists */
  {
    sfree (set_key);
  }

  metric->updates_num++;

  pthread_mutex_unlock (&metrics_lock);
  return (0);
}