static int statsd_metric_submit_unsafe(char const *name,
                                       statsd_metric_t *metric) /* {{{ */
{
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = NAN};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "statsd", sizeof(vl.plugin));

  if (metric->type == STATSD_GAUGE)
    sstrncpy(vl.type, "gauge", sizeof(vl.type));
  else if (metric->type == STATSD_TIMER)
    sstrncpy(vl.type, "latency", sizeof(vl.type));
  else if (metric->type == STATSD_SET)
    sstrncpy(vl.type, "objects", sizeof(vl.type));
  else /* if (metric->type == STATSD_COUNTER) */
    sstrncpy(vl.type, "derive", sizeof(vl.type));

  sstrncpy(vl.type_instance, name, sizeof(vl.type_instance));

  if (metric->type == STATSD_GAUGE)
    vl.values[0].gauge = (gauge_t)metric->value;
  else if (metric->type == STATSD_TIMER) {
    _Bool have_events = (metric->updates_num > 0);

    /* Make sure all timer metrics share the *same* timestamp. */
    vl.time = cdtime();

    ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-average", name);
    vl.values[0].gauge =
        have_events
            ? CDTIME_T_TO_DOUBLE(latency_counter_get_average(metric->latency))
            : NAN;
    plugin_dispatch_values(&vl);

    if (conf_timer_lower) {
      ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-lower", name);
      vl.values[0].gauge =
          have_events
              ? CDTIME_T_TO_DOUBLE(latency_counter_get_min(metric->latency))
              : NAN;
      plugin_dispatch_values(&vl);
    }

    if (conf_timer_upper) {
      ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-upper", name);
      vl.values[0].gauge =
          have_events
              ? CDTIME_T_TO_DOUBLE(latency_counter_get_max(metric->latency))
              : NAN;
      plugin_dispatch_values(&vl);
    }

    if (conf_timer_sum) {
      ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-sum", name);
      vl.values[0].gauge =
          have_events
              ? CDTIME_T_TO_DOUBLE(latency_counter_get_sum(metric->latency))
              : NAN;
      plugin_dispatch_values(&vl);
    }

    for (size_t i = 0; i < conf_timer_percentile_num; i++) {
      ssnprintf(vl.type_instance, sizeof(vl.type_instance),
                "%s-percentile-%.0f", name, conf_timer_percentile[i]);
      vl.values[0].gauge =
          have_events ? CDTIME_T_TO_DOUBLE(latency_counter_get_percentile(
                            metric->latency, conf_timer_percentile[i]))
                      : NAN;
      plugin_dispatch_values(&vl);
    }

    /* Keep this at the end, since vl.type is set to "gauge" here. The
     * vl.type's above are implicitly set to "latency". */
    if (conf_timer_count) {
      sstrncpy(vl.type, "gauge", sizeof(vl.type));
      ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-count", name);
      vl.values[0].gauge = latency_counter_get_num(metric->latency);
      plugin_dispatch_values(&vl);
    }

    latency_counter_reset(metric->latency);
    return (0);
  } else if (metric->type == STATSD_SET) {
    if (metric->set == NULL)
      vl.values[0].gauge = 0.0;
    else
      vl.values[0].gauge = (gauge_t)c_avl_size(metric->set);
  } else { /* STATSD_COUNTER */
    gauge_t delta = nearbyint(metric->value);

    /* Etsy's statsd writes counters as two metrics: a rate and the change since
     * the last write. Since collectd does not reset its DERIVE metrics to zero,
     * this makes little sense, but we're dispatching a "count" metric here
     * anyway - if requested by the user - for compatibility reasons. */
    if (conf_counter_sum) {
      sstrncpy(vl.type, "count", sizeof(vl.type));
      vl.values[0].gauge = delta;
      plugin_dispatch_values(&vl);

      /* restore vl.type */
      sstrncpy(vl.type, "derive", sizeof(vl.type));
    }

    /* Rather than resetting value to zero, subtract delta so we correctly keep
     * track of residuals. */
    metric->value -= delta;
    metric->counter += (derive_t)delta;

    vl.values[0].derive = metric->counter;
  }

  return (plugin_dispatch_values(&vl));
}