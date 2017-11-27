static int c_ipmi_config(const char *key, const char *value) {
  if (ignorelist == NULL)
    ignorelist = ignorelist_create(/* invert = */ 1);
  if (ignorelist == NULL)
    return (1);

  if (strcasecmp("Sensor", key) == 0) {
    ignorelist_add(ignorelist, value);
  } else if (strcasecmp("IgnoreSelected", key) == 0) {
    int invert = 1;
    if (IS_TRUE(value))
      invert = 0;
    ignorelist_set_invert(ignorelist, invert);
  } else if (strcasecmp("NotifySensorAdd", key) == 0) {
    if (IS_TRUE(value))
      c_ipmi_nofiy_add = 1;
  } else if (strcasecmp("NotifySensorRemove", key) == 0) {
    if (IS_TRUE(value))
      c_ipmi_nofiy_remove = 1;
  } else if (strcasecmp("NotifySensorNotPresent", key) == 0) {
    if (IS_TRUE(value))
      c_ipmi_nofiy_notpresent = 1;
  } else {
    return (-1);
  }

  return (0);
}