static int smart_config(const char *key, const char *value) {
  if (ignorelist == NULL)
    ignorelist = ignorelist_create(/* invert = */ 1);
  if (ignorelist == NULL)
    return 1;

  if (strcasecmp("Disk", key) == 0) {
    ignorelist_add(ignorelist, value);
  } else if (strcasecmp("IgnoreSelected", key) == 0) {
    int invert = 1;
    if (IS_TRUE(value))
      invert = 0;
    ignorelist_set_invert(ignorelist, invert);
  } else if (strcasecmp("IgnoreSleepMode", key) == 0) {
    if (IS_TRUE(value))
      ignore_sleep_mode = 1;
  } else if (strcasecmp("UseSerial", key) == 0) {
    if (IS_TRUE(value))
      use_serial = 1;
  } else {
    return -1;
  }

  return 0;
}