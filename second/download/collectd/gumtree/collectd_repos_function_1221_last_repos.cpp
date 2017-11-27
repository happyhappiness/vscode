static void tss2_submit_io(const char *plugin_instance, const char *type,
                           derive_t rx, derive_t tx) {
  /*
   * Submits the io rx/tx tuple to the collectd daemon
   */
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.derive = rx}, {.derive = tx},
  };

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "teamspeak2", sizeof(vl.plugin));

  if (plugin_instance != NULL)
    sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));

  sstrncpy(vl.type, type, sizeof(vl.type));

  plugin_dispatch_values(&vl);
}