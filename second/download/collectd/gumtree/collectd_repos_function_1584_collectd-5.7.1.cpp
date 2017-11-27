static int latency_submit_match(cu_match_t *match, void *user_data) {
  cu_tail_match_simple_t *data = (cu_tail_match_simple_t *)user_data;
  cu_match_value_t *match_value;
  value_list_t vl = VALUE_LIST_INIT;

  match_value = (cu_match_value_t *)match_get_user_data(match);
  if (match_value == NULL)
    return (-1);

  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, data->plugin, sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, data->plugin_instance,
           sizeof(vl.plugin_instance));
  vl.interval = data->interval;
  vl.time = cdtime();

  /* Submit percentiles */
  sstrncpy(vl.type, data->type, sizeof(vl.type));
  for (size_t i = 0; i < data->latency_config.percentile_num; i++) {
    if (strlen(data->type_instance) != 0)
      ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-%.0f",
                data->type_instance, data->latency_config.percentile[i]);
    else
      ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%.0f",
                data->latency_config.percentile[i]);

    vl.values = &(value_t){
        .gauge =
            (match_value->values_num != 0)
                ? CDTIME_T_TO_DOUBLE(latency_counter_get_percentile(
                      match_value->latency, data->latency_config.percentile[i]))
                : NAN,
    };
    vl.values_len = 1;

    plugin_dispatch_values(&vl);
  }

  /* Submit buckets */
  sstrncpy(vl.type, "bucket", sizeof(vl.type));
  for (size_t i = 0; i < data->latency_config.buckets_num; i++) {
    latency_bucket_t bucket = data->latency_config.buckets[i];

    double lower_bound = CDTIME_T_TO_DOUBLE(bucket.lower_bound);
    double upper_bound =
        bucket.upper_bound ? CDTIME_T_TO_DOUBLE(bucket.upper_bound) : INFINITY;

    if (strlen(data->type_instance) != 0)
      ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-%s-%g_%g",
                data->type, data->type_instance, lower_bound, upper_bound);
    else
      ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-%g_%g",
                data->type, lower_bound, upper_bound);

    vl.values = &(value_t){
        .gauge =
            latency_counter_get_rate(match_value->latency, bucket.lower_bound,
                                     bucket.upper_bound, vl.time),
    };
    vl.values_len = 1;

    plugin_dispatch_values(&vl);
  }

  match_value->value.gauge = NAN;
  match_value->values_num = 0;
  latency_counter_reset(match_value->latency);

  return (0);
}