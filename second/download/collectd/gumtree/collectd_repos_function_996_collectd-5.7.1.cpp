static int cgroups_config(const char *key, const char *value) {
  cgroups_init();

  if (strcasecmp(key, "CGroup") == 0) {
    if (ignorelist_add(il_cgroup, value))
      return (1);
    return (0);
  } else if (strcasecmp(key, "IgnoreSelected") == 0) {
    if (IS_TRUE(value))
      ignorelist_set_invert(il_cgroup, 0);
    else
      ignorelist_set_invert(il_cgroup, 1);
    return (0);
  }

  return (-1);
}