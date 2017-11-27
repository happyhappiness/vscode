static int statsd_config(oconfig_item_t *ci) /* {{{ */
{
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Host", child->key) == 0)
      cf_util_get_string(child, &conf_node);
    else if (strcasecmp("Port", child->key) == 0)
      cf_util_get_service(child, &conf_service);
    else if (strcasecmp("DeleteCounters", child->key) == 0)
      cf_util_get_boolean(child, &conf_delete_counters);
    else if (strcasecmp("DeleteTimers", child->key) == 0)
      cf_util_get_boolean(child, &conf_delete_timers);
    else if (strcasecmp("DeleteGauges", child->key) == 0)
      cf_util_get_boolean(child, &conf_delete_gauges);
    else if (strcasecmp("DeleteSets", child->key) == 0)
      cf_util_get_boolean(child, &conf_delete_sets);
    else if (strcasecmp("CounterSum", child->key) == 0)
      cf_util_get_boolean(child, &conf_counter_sum);
    else if (strcasecmp("TimerLower", child->key) == 0)
      cf_util_get_boolean(child, &conf_timer_lower);
    else if (strcasecmp("TimerUpper", child->key) == 0)
      cf_util_get_boolean(child, &conf_timer_upper);
    else if (strcasecmp("TimerSum", child->key) == 0)
      cf_util_get_boolean(child, &conf_timer_sum);
    else if (strcasecmp("TimerCount", child->key) == 0)
      cf_util_get_boolean(child, &conf_timer_count);
    else if (strcasecmp("TimerPercentile", child->key) == 0)
      statsd_config_timer_percentile(child);
    else
      ERROR("statsd plugin: The \"%s\" config option is not valid.",
            child->key);
  }

  return (0);
}