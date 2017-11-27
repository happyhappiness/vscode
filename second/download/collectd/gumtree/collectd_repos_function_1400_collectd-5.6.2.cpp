static void tt_submit(gauge_t val, const char *type) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = val;

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);

  sstrncpy(vl.host, config_host, sizeof(vl.host));
  sstrncpy(vl.plugin, "tokyotyrant", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, config_port, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));

  plugin_dispatch_values(&vl);
}