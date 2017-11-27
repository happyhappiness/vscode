static void pmu_submit_counter(int cpu, char *event, counter_t value,
                               meta_data_t *meta) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.counter = value};
  vl.values_len = 1;

  sstrncpy(vl.plugin, PMU_PLUGIN, sizeof(vl.plugin));
  if (cpu == -1) {
    snprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "all");
  } else {
    vl.meta = meta;
    snprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%d", cpu);
  }
  sstrncpy(vl.type, "counter", sizeof(vl.type));
  sstrncpy(vl.type_instance, event, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}