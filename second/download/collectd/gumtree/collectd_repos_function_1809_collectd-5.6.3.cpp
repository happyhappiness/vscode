static int ted_config(const char *key, const char *value) {
  if (strcasecmp("Device", key) == 0) {
    sfree(conf_device);
    conf_device = sstrdup(value);
  } else if (strcasecmp("Retries", key) == 0) {
    int tmp;

    tmp = atoi(value);
    if (tmp < 0) {
      WARNING("ted plugin: Invalid retry count: %i", tmp);
      return (1);
    }
    conf_retries = tmp;
  } else {
    ERROR("ted plugin: Unknown config option: %s", key);
    return (-1);
  }

  return (0);
}