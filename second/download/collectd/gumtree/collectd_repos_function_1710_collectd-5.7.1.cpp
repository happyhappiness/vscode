static int statsd_read(void) /* {{{ */
{
  c_avl_iterator_t *iter;
  char *name;
  statsd_metric_t *metric;

  char **to_be_deleted = NULL;
  size_t to_be_deleted_num = 0;

  pthread_mutex_lock(&metrics_lock);

  if (metrics_tree == NULL) {
    pthread_mutex_unlock(&metrics_lock);
    return (0);
  }

  iter = c_avl_get_iterator(metrics_tree);
  while (c_avl_iterator_next(iter, (void *)&name, (void *)&metric) == 0) {
    if ((metric->updates_num == 0) &&
        ((conf_delete_counters && (metric->type == STATSD_COUNTER)) ||
         (conf_delete_timers && (metric->type == STATSD_TIMER)) ||
         (conf_delete_gauges && (metric->type == STATSD_GAUGE)) ||
         (conf_delete_sets && (metric->type == STATSD_SET)))) {
      DEBUG("statsd plugin: Deleting metric \"%s\".", name);
      strarray_add(&to_be_deleted, &to_be_deleted_num, name);
      continue;
    }

    /* Names have a prefix, e.g. "c:", which determines the (statsd) type.
     * Remove this here. */
    statsd_metric_submit_unsafe(name + 2, metric);

    /* Reset the metric. */
    metric->updates_num = 0;
    if (metric->type == STATSD_SET)
      statsd_metric_clear_set_unsafe(metric);
  }
  c_avl_iterator_destroy(iter);

  for (size_t i = 0; i < to_be_deleted_num; i++) {
    int status;

    status = c_avl_remove(metrics_tree, to_be_deleted[i], (void *)&name,
                          (void *)&metric);
    if (status != 0) {
      ERROR("stats plugin: c_avl_remove (\"%s\") failed with status %i.",
            to_be_deleted[i], status);
      continue;
    }

    sfree(name);
    statsd_metric_free(metric);
  }

  pthread_mutex_unlock(&metrics_lock);

  strarray_free(to_be_deleted, to_be_deleted_num);

  return (0);
}