static int metric_update(Io__Prometheus__Client__Metric *m, value_t value,
                         int ds_type, cdtime_t t, cdtime_t interval) {
  if (ds_type == DS_TYPE_GAUGE) {
    sfree(m->counter);
    if (m->gauge == NULL) {
      m->gauge = calloc(1, sizeof(*m->gauge));
      if (m->gauge == NULL)
        return ENOMEM;
      io__prometheus__client__gauge__init(m->gauge);
    }

    m->gauge->value = (double)value.gauge;
    m->gauge->has_value = 1;
  } else { /* not gauge */
    sfree(m->gauge);
    if (m->counter == NULL) {
      m->counter = calloc(1, sizeof(*m->counter));
      if (m->counter == NULL)
        return ENOMEM;
      io__prometheus__client__counter__init(m->counter);
    }

    switch (ds_type) {
    case DS_TYPE_ABSOLUTE:
      m->counter->value = (double)value.absolute;
      break;
    case DS_TYPE_COUNTER:
      m->counter->value = (double)value.counter;
      break;
    default:
      m->counter->value = (double)value.derive;
      break;
    }
    m->counter->has_value = 1;
  }

  /* Prometheus has a globally configured timeout after which metrics are
   * considered stale. This causes problems when metrics have an interval
   * exceeding that limit. We emulate the behavior of "pushgateway" and *not*
   * send a timestamp value – Prometheus will fill in the current time. */
  if (interval <= staleness_delta) {
    m->timestamp_ms = CDTIME_T_TO_MS(t);
    m->has_timestamp_ms = 1;
  } else {
    static c_complain_t long_metric = C_COMPLAIN_INIT_STATIC;
    c_complain(
        LOG_NOTICE, &long_metric,
        "write_prometheus plugin: You have metrics with an interval exceeding "
        "\"StalenessDelta\" setting (%.3fs). This is suboptimal, please check "
        "the collectd.conf(5) manual page to understand what's going on.",
        CDTIME_T_TO_DOUBLE(staleness_delta));

    m->timestamp_ms = 0;
    m->has_timestamp_ms = 0;
  }

  return 0;
}