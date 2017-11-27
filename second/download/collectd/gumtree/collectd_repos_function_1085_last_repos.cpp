static int mbmon_config(const char *key, const char *value) {
  if (strcasecmp(key, "host") == 0) {
    if (mbmon_host != NULL)
      free(mbmon_host);
    mbmon_host = strdup(value);
  } else if (strcasecmp(key, "port") == 0) {
    if (mbmon_port != NULL)
      free(mbmon_port);
    mbmon_port = strdup(value);
  } else {
    return -1;
  }

  return 0;
}