static int md_config(const char *key, const char *value) {
  if (ignorelist == NULL)
    ignorelist = ignorelist_create(/* invert = */ 1);
  if (ignorelist == NULL)
    return 1;

  if (strcasecmp(key, "Device") == 0) {
    ignorelist_add(ignorelist, value);
  } else if (strcasecmp(key, "IgnoreSelected") == 0) {
    ignorelist_set_invert(ignorelist, IS_TRUE(value) ? 0 : 1);
  } else {
    return -1;
  }

  return 0;
}