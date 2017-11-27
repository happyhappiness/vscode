static void serial_submit(const char *type_instance, derive_t rx, derive_t tx) {
  value_t values[2];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].derive = rx;
  values[1].derive = tx;

  vl.values = values;
  vl.values_len = 2;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "serial", sizeof(vl.plugin));
  sstrncpy(vl.type, "serial_octets", sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}