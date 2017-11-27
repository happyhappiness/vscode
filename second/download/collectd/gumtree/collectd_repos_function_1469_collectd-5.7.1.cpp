static void tt_submit(gauge_t value, const char *type) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;

  sstrncpy(vl.host, config_host, sizeof(vl.host));
  sstrncpy(vl.plugin, "tokyotyrant", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, config_port, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));

  plugin_dispatch_values(&vl);
}