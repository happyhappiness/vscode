static int ctail_config_add_match_dstype(ctail_config_match_t *cm,
                                         oconfig_item_t *ci) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("tail plugin: `DSType' needs exactly one string argument.");
    return -1;
  }

  char const *ds_type = ci->values[0].value.string;
  if (strncasecmp("Gauge", ds_type, strlen("Gauge")) == 0) {
    cm->flags = UTILS_MATCH_DS_TYPE_GAUGE;
    if (strcasecmp("GaugeAverage", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_GAUGE_AVERAGE;
    else if (strcasecmp("GaugeMin", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_GAUGE_MIN;
    else if (strcasecmp("GaugeMax", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_GAUGE_MAX;
    else if (strcasecmp("GaugeLast", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_GAUGE_LAST;
    else if (strcasecmp("GaugeInc", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_GAUGE_INC;
    else if (strcasecmp("GaugeAdd", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_GAUGE_ADD;
    else if (strcasecmp("GaugePersist", ci->values[0].value.string) == 0)
      cm->flags |= UTILS_MATCH_CF_GAUGE_PERSIST;
    else
      cm->flags = 0;
  } else if (strcasecmp("Distribution", ds_type) == 0) {
    cm->flags = UTILS_MATCH_DS_TYPE_GAUGE | UTILS_MATCH_CF_GAUGE_DIST;

    int status = latency_config(&cm->latency, ci, "tail");
    if (status != 0)
      return status;
  } else if (strncasecmp("Counter", ds_type, strlen("Counter")) == 0) {
    cm->flags = UTILS_MATCH_DS_TYPE_COUNTER;
    if (strcasecmp("CounterSet", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_COUNTER_SET;
    else if (strcasecmp("CounterAdd", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_COUNTER_ADD;
    else if (strcasecmp("CounterInc", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_COUNTER_INC;
    else
      cm->flags = 0;
  } else if (strncasecmp("Derive", ds_type, strlen("Derive")) == 0) {
    cm->flags = UTILS_MATCH_DS_TYPE_DERIVE;
    if (strcasecmp("DeriveSet", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_DERIVE_SET;
    else if (strcasecmp("DeriveAdd", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_DERIVE_ADD;
    else if (strcasecmp("DeriveInc", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_DERIVE_INC;
    else
      cm->flags = 0;
  } else if (strncasecmp("Absolute", ds_type, strlen("Absolute")) == 0) {
    cm->flags = UTILS_MATCH_DS_TYPE_ABSOLUTE;
    if (strcasecmp("AbsoluteSet", ds_type) == 0)
      cm->flags |= UTILS_MATCH_CF_ABSOLUTE_SET;
    else
      cm->flags = 0;
  } else {
    cm->flags = 0;
  }

  if (cm->flags == 0) {
    WARNING("tail plugin: `%s' is not a valid argument to `DSType'.",
            ci->values[0].value.string);
    return -1;
  }

  return 0;
}