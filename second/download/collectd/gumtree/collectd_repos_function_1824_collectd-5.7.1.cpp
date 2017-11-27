static void match_simple_free(void *data) {
  cu_match_value_t *user_data = (cu_match_value_t *)data;
  if (user_data->latency)
    latency_counter_destroy(user_data->latency);

  free(data);
}