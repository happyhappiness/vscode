static void ps_submit_state(const char *state, double value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "processes", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, "", sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "ps_state", sizeof(vl.type));
  sstrncpy(vl.type_instance, state, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}