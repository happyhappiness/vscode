static statsd_metric_t *statsd_metric_lookup_unsafe (char const *name, /* {{{ */
    metric_type_t type)
{
  char key[DATA_MAX_NAME_LEN + 2];
  char *key_copy;
  statsd_metric_t *metric;
  int status;

  switch (type)
  {
    case STATSD_COUNTER: key[0] = 'c'; break;
    case STATSD_TIMER:   key[0] = 't'; break;
    case STATSD_GAUGE:   key[0] = 'g'; break;
    case STATSD_SET:     key[0] = 's'; break;
    default: return (NULL);
  }

  key[1] = ':';
  sstrncpy (&key[2], name, sizeof (key) - 2);

  status = c_avl_get (metrics_tree, key, (void *) &metric);
  if (status == 0)
    return (metric);

  key_copy = strdup (key);
  if (key_copy == NULL)
  {
    ERROR ("statsd plugin: strdup failed.");
    return (NULL);
  }

  metric = malloc (sizeof (*metric));
  if (metric == NULL)
  {
    ERROR ("statsd plugin: malloc failed.");
    sfree (key_copy);
    return (NULL);
  }
  memset (metric, 0, sizeof (*metric));

  metric->type = type;
  metric->latency = NULL;
  metric->set = NULL;

  status = c_avl_insert (metrics_tree, key_copy, metric);
  if (status != 0)
  {
    ERROR ("statsd plugin: c_avl_insert failed.");
    sfree (key_copy);
    sfree (metric);
    return (NULL);
  }

  return (metric);
}