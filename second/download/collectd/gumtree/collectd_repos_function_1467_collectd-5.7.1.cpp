static int tt_config(const char *key, const char *value) {
  if (strcasecmp("Host", key) == 0) {
    char *temp;

    temp = strdup(value);
    if (temp == NULL) {
      ERROR("tokyotyrant plugin: Host strdup failed.");
      return (1);
    }
    sfree(config_host);
    config_host = temp;
  } else if (strcasecmp("Port", key) == 0) {
    char *temp;

    temp = strdup(value);
    if (temp == NULL) {
      ERROR("tokyotyrant plugin: Port strdup failed.");
      return (1);
    }
    sfree(config_port);
    config_port = temp;
  } else {
    ERROR("tokyotyrant plugin: error: unrecognized configuration key %s", key);
    return (-1);
  }

  return (0);
}