static void multimeter_submit(double value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "multimeter", sizeof(vl.plugin));
  sstrncpy(vl.type, "multimeter", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}