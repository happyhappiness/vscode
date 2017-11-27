static int protocols_config(const char *key, const char *value) {
  if (values_list == NULL)
    values_list = ignorelist_create(/* invert = */ 1);

  if (strcasecmp(key, "Value") == 0) {
    ignorelist_add(values_list, value);
  } else if (strcasecmp(key, "IgnoreSelected") == 0) {
    int invert = 1;
    if (IS_TRUE(value))
      invert = 0;
    ignorelist_set_invert(values_list, invert);
  } else {
    return (-1);
  }

  return (0);
}