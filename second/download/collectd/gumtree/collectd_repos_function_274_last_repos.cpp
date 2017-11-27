static void thermal_submit(const char *plugin_instance, enum dev_type dt,
                           value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &value;
  vl.values_len = 1;

  sstrncpy(vl.plugin, "thermal", sizeof(vl.plugin));
  if (plugin_instance != NULL)
    sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, (dt == TEMP) ? "temperature" : "gauge", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}