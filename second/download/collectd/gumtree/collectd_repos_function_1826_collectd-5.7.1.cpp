cu_match_t *match_create_simple(const char *regex, const char *excluderegex,
                                int match_ds_type) {
  cu_match_value_t *user_data;
  cu_match_t *obj;

  user_data = calloc(1, sizeof(*user_data));
  if (user_data == NULL)
    return (NULL);
  user_data->ds_type = match_ds_type;

  if ((match_ds_type & UTILS_MATCH_DS_TYPE_GAUGE) &&
      (match_ds_type & UTILS_MATCH_CF_GAUGE_DIST)) {
    user_data->latency = latency_counter_create();
    if (user_data->latency == NULL) {
      ERROR("match_create_simple(): latency_counter_create() failed.");
      free(user_data);
      return (NULL);
    }
  }

  obj = match_create_callback(regex, excluderegex, default_callback, user_data,
                              match_simple_free);
  if (obj == NULL) {
    if (user_data->latency)
      latency_counter_destroy(user_data->latency);

    sfree(user_data);
    return (NULL);
  }
  return (obj);
}