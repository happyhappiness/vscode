static void cpusleep_submit(derive_t cpu_sleep) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].derive = cpu_sleep;

  vl.values = values;
  vl.values_len = 1;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "cpusleep", sizeof(vl.plugin));
  sstrncpy(vl.type, "total_time_in_ms", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}