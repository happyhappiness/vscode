static void cpusleep_submit(derive_t cpu_sleep) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.derive = cpu_sleep};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "cpusleep", sizeof(vl.plugin));
  sstrncpy(vl.type, "total_time_in_ms", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}