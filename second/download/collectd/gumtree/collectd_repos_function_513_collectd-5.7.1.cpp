static void if_submit(const char *dev, const char *type, derive_t rx,
                      derive_t tx) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.derive = rx}, {.derive = tx},
  };

  if (ignorelist_match(ignorelist, dev) != 0)
    return;

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "interface", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, dev, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));

  plugin_dispatch_values(&vl);
}