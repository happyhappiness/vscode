static void as_submit(const char *type, const char *type_instance, double val) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = val};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "apple_sensors", sizeof(vl.plugin));
  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}