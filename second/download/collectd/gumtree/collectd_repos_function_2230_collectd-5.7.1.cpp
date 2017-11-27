static void cipvs_submit_connections(const char *pi, const char *ti,
                                     derive_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.derive = value};
  vl.values_len = 1;

  sstrncpy(vl.plugin, "ipvs", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, pi, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "connections", sizeof(vl.type));
  sstrncpy(vl.type_instance, (NULL != ti) ? ti : "total",
           sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
  return;
}