static void lpar_submit(const char *type_instance, double value) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = (gauge_t)value;

  vl.values = values;
  vl.values_len = 1;
  if (report_by_serial) {
    sstrncpy(vl.host, serial, sizeof(vl.host));
    sstrncpy(vl.plugin_instance, hostname_g, sizeof(vl.plugin));
  } else {
    sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  }
  sstrncpy(vl.plugin, "lpar", sizeof(vl.plugin));
  sstrncpy(vl.type, "vcpu", sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}