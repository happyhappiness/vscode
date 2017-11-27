static void users_submit(gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "users", sizeof(vl.plugin));
  sstrncpy(vl.type, "users", sizeof(vl.plugin));

  plugin_dispatch_values(&vl);
}