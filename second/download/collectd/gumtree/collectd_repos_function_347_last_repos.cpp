static void submit_io_time(char const *plugin_instance, derive_t io_time,
                           derive_t weighted_time) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.derive = io_time}, {.derive = weighted_time},
  };

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "disk", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "disk_io_time", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}