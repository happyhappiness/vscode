static void fhcount_submit(const char *type, const char *type_instance,
                           gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;

  // Compose the metric
  sstrncpy(vl.plugin, "fhcount", sizeof(vl.plugin));
  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  // Dispatch the metric
  plugin_dispatch_values(&vl);
}