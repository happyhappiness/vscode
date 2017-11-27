static int statsd_handle_gauge(char const *name, /* {{{ */
                               char const *value_str) {
  value_t value;
  int status;

  value.gauge = 0;
  status = statsd_parse_value(value_str, &value);
  if (status != 0)
    return (status);

  if ((value_str[0] == '+') || (value_str[0] == '-'))
    return (statsd_metric_add(name, (double)value.gauge, STATSD_GAUGE));
  else
    return (statsd_metric_set(name, (double)value.gauge, STATSD_GAUGE));
}