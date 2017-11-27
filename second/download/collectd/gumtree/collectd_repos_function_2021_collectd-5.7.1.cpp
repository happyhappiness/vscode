static void submit_value(int cpu_num, gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;

  sstrncpy(vl.plugin, "xencpu", sizeof(vl.plugin));
  sstrncpy(vl.type, "percent", sizeof(vl.type));
  sstrncpy(vl.type_instance, "load", sizeof(vl.type_instance));

  if (cpu_num >= 0) {
    ssnprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%i", cpu_num);
  }
  plugin_dispatch_values(&vl);
}