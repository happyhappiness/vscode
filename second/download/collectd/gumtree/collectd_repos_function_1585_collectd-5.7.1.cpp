static void tail_match_simple_free(void *data) {
  cu_tail_match_simple_t *user_data = (cu_tail_match_simple_t *)data;
  latency_config_free(user_data->latency_config);
  sfree(user_data);
}