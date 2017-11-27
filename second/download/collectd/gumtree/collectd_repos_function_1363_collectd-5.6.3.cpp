static void fhcount_submit(const char *type, const char *type_instance,
                           gauge_t value) {

  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = value;

  vl.values = values;
  vl.values_len = 1;

  // Compose the metric
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "fhcount", sizeof(vl.plugin));
  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  // Dispatch the metric
  plugin_dispatch_values(&vl);
}