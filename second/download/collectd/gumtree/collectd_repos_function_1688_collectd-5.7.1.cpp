static void cpufreq_submit(int cpu_num, value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &value;
  vl.values_len = 1;
  sstrncpy(vl.plugin, "cpufreq", sizeof(vl.plugin));
  sstrncpy(vl.type, "cpufreq", sizeof(vl.type));
  ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%i", cpu_num);

  plugin_dispatch_values(&vl);
}