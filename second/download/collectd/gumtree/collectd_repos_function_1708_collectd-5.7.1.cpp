static int statsd_metric_clear_set_unsafe(statsd_metric_t *metric) /* {{{ */
{
  void *key;
  void *value;

  if ((metric == NULL) || (metric->type != STATSD_SET))
    return (EINVAL);

  if (metric->set == NULL)
    return (0);

  while (c_avl_pick(metric->set, &key, &value) == 0) {
    sfree(key);
    sfree(value);
  }

  return (0);
}