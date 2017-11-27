static void battery_submit(const char *type, gauge_t value,
                           const char *type_instance) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "battery", sizeof(vl.plugin));
  /* statefs supports 1 battery at present */
  sstrncpy(vl.plugin_instance, "0", sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_instance != NULL)
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));
  plugin_dispatch_values(&vl);
}