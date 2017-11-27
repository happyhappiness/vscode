static int madwifi_config(const char *key, const char *value) {
  if (init_state != 1)
    madwifi_real_init();
  init_state = 1;

  if (ignorelist == NULL)
    ignorelist = ignorelist_create(/* invert = */ 1);

  if (strcasecmp(key, "Interface") == 0)
    ignorelist_add(ignorelist, value);

  else if (strcasecmp(key, "IgnoreSelected") == 0)
    ignorelist_set_invert(ignorelist, IS_TRUE(value) ? 0 : 1);

  else if (strcasecmp(key, "Source") == 0) {
    if (strcasecmp(value, "ProcFS") == 0)
      use_sysfs = 0;
    else if (strcasecmp(value, "SysFS") == 0)
      use_sysfs = 1;
    else {
      ERROR("madwifi plugin: The argument of the `Source' "
            "option must either be `SysFS' or "
            "`ProcFS'.");
      return -1;
    }
  }

  else if (strcasecmp(key, "WatchSet") == 0) {
    if (strcasecmp(value, "All") == 0)
      watchlist_set(watch_items, 0xFFFFFFFF);
    else if (strcasecmp(value, "None") == 0)
      watchlist_set(watch_items, 0);
    else
      return -1;
  }

  else if (strcasecmp(key, "WatchAdd") == 0) {
    int id = watchitem_find(value);

    if (id < 0)
      return (-1);
    else
      watchlist_add(watch_items, id);
  }

  else if (strcasecmp(key, "WatchRemove") == 0) {
    int id = watchitem_find(value);

    if (id < 0)
      return (-1);
    else
      watchlist_remove(watch_items, id);
  }

  else if (strcasecmp(key, "MiscSet") == 0) {
    if (strcasecmp(value, "All") == 0)
      watchlist_set(misc_items, 0xFFFFFFFF);
    else if (strcasecmp(value, "None") == 0)
      watchlist_set(misc_items, 0);
    else
      return -1;
  }

  else if (strcasecmp(key, "MiscAdd") == 0) {
    int id = watchitem_find(value);

    if (id < 0)
      return (-1);
    else
      watchlist_add(misc_items, id);
  }

  else if (strcasecmp(key, "MiscRemove") == 0) {
    int id = watchitem_find(value);

    if (id < 0)
      return (-1);
    else
      watchlist_remove(misc_items, id);
  }

  else
    return (-1);

  return (0);
}