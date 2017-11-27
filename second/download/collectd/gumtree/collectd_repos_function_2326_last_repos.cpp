void curl_stats_destroy(curl_stats_t *s) {
  if (s != NULL)
    free(s);
}