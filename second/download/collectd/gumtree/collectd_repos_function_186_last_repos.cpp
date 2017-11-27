static void submit(const char *host, const char *type, /* {{{ */
                   gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "ping", sizeof(vl.plugin));
  sstrncpy(vl.type_instance, host, sizeof(vl.type_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));

  plugin_dispatch_values(&vl);
}