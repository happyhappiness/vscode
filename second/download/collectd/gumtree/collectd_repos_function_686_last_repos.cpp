static void ps_submit_fork_rate(derive_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.derive = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "processes", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, "", sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "fork_rate", sizeof(vl.type));
  sstrncpy(vl.type_instance, "", sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}