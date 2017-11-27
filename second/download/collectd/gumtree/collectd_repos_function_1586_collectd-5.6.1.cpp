static int statsd_metric_set (char const *name, double value, /* {{{ */
    metric_type_t type)
{
  statsd_metric_t *metric;

  pthread_mutex_lock (&metrics_lock);

  metric = statsd_metric_lookup_unsafe (name, type);
  if (metric == NULL)
  {
    pthread_mutex_unlock (&metrics_lock);
    return (-1);
  }

  metric->value = value;
  metric->updates_num++;

  pthread_mutex_unlock (&metrics_lock);

  return (0);
}