static void tape_submit(const char *plugin_instance, const char *type,
                        derive_t read, derive_t write) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.derive = read}, {.derive = write},
  };

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "tape", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));

  plugin_dispatch_values(&vl);
}