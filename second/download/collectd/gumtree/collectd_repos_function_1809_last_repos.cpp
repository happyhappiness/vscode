static int statsd_handle_timer(char const *name, /* {{{ */
                               char const *value_str, char const *extra) {
  statsd_metric_t *metric;
  value_t value_ms;
  value_t scale;
  cdtime_t value;
  int status;

  if ((extra != NULL) && (extra[0] != '@'))
    return -1;

  scale.gauge = 1.0;
  if (extra != NULL) {
    status = statsd_parse_value(extra + 1, &scale);
    if (status != 0)
      return status;

    if (!isfinite(scale.gauge) || (scale.gauge <= 0.0) || (scale.gauge > 1.0))
      return -1;
  }

  value_ms.derive = 0;
  status = statsd_parse_value(value_str, &value_ms);
  if (status != 0)
    return status;

  value = MS_TO_CDTIME_T(value_ms.gauge / scale.gauge);

  pthread_mutex_lock(&metrics_lock);

  metric = statsd_metric_lookup_unsafe(name, STATSD_TIMER);
  if (metric == NULL) {
    pthread_mutex_unlock(&metrics_lock);
    return -1;
  }

  if (metric->latency == NULL)
    metric->latency = latency_counter_create();
  if (metric->latency == NULL) {
    pthread_mutex_unlock(&metrics_lock);
    return -1;
  }

  latency_counter_add(metric->latency, value);
  metric->updates_num++;

  pthread_mutex_unlock(&metrics_lock);
  return 0;
}