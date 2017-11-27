static int sensors_config(const char *key, const char *value) {
  if (sensor_list == NULL)
    sensor_list = ignorelist_create(1);

  /* TODO: This setting exists for compatibility with old versions of
   * lm-sensors. Remove support for those ancient versions in the next
   * major release. */
  if (strcasecmp(key, "SensorConfigFile") == 0) {
    char *tmp = strdup(value);
    if (tmp != NULL) {
      sfree(conffile);
      conffile = tmp;
    }
  } else if (strcasecmp(key, "Sensor") == 0) {
    if (ignorelist_add(sensor_list, value)) {
      ERROR("sensors plugin: "
            "Cannot add value to ignorelist.");
      return (1);
    }
  } else if (strcasecmp(key, "IgnoreSelected") == 0) {
    ignorelist_set_invert(sensor_list, 1);
    if (IS_TRUE(value))
      ignorelist_set_invert(sensor_list, 0);
  }
#if (SENSORS_API_VERSION >= 0x400) && (SENSORS_API_VERSION < 0x500)
  else if (strcasecmp(key, "UseLabels") == 0) {
    use_labels = IS_TRUE(value) ? 1 : 0;
  }
#endif
  else {
    return (-1);
  }

  return (0);
}