static void fscache_submit(const char *section, const char *name,
                           value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &value;
  vl.values_len = 1;

  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "fscache", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, section, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "fscache_stat", sizeof(vl.type));
  sstrncpy(vl.type_instance, name, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}