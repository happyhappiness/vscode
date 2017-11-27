static int statsd_handle_counter(char const *name, /* {{{ */
                                 char const *value_str, char const *extra) {
  value_t value;
  value_t scale;
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

  value.gauge = 1.0;
  status = statsd_parse_value(value_str, &value);
  if (status != 0)
    return status;

  /* Changes to the counter are added to (statsd_metric_t*)->value. ->counter is
   * only updated in statsd_metric_submit_unsafe(). */
  return statsd_metric_add(name, (double)(value.gauge / scale.gauge),
                           STATSD_COUNTER);
}