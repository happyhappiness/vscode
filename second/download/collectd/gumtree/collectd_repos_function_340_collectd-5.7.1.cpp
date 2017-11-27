static void submit_value(int cpu_num, int cpu_state, const char *type,
                         value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &value;
  vl.values_len = 1;

  sstrncpy(vl.plugin, "cpu", sizeof(vl.plugin));
  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, cpu_state_names[cpu_state],
           sizeof(vl.type_instance));

  if (cpu_num >= 0) {
    ssnprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%i", cpu_num);
  }
  plugin_dispatch_values(&vl);
}