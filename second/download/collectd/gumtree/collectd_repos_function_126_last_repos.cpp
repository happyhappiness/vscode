static void dpdk_stats_counter_submit(const char *plugin_instance,
                                      const char *cnt_name, derive_t value,
                                      cdtime_t port_read_time) {
  value_list_t vl = VALUE_LIST_INIT;
  vl.values = &(value_t){.derive = value};
  vl.values_len = 1;
  vl.time = port_read_time;
  sstrncpy(vl.plugin, DPDK_STATS_PLUGIN, sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  dpdk_stats_resolve_cnt_type(vl.type, sizeof(vl.type), cnt_name);
  sstrncpy(vl.type_instance, cnt_name, sizeof(vl.type_instance));
  plugin_dispatch_values(&vl);
}