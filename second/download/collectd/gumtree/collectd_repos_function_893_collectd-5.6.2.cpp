static void turbostat_submit(const char *plugin_instance, const char *type,
                             const char *type_instance, gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t v;

  v.gauge = value;
  vl.values = &v;
  vl.values_len = 1;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, PLUGIN_NAME, sizeof(vl.plugin));
  if (plugin_instance != NULL)
    sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_instance != NULL)
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}