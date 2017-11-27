static void ntpd_submit(const char *type, const char *type_inst,
                        gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "ntpd", sizeof(vl.plugin));
  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, type_inst, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}