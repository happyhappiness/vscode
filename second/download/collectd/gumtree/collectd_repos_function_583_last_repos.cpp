static void dpdk_events_gauge_submit(const char *plugin_instance,
                                     const char *type_instance, gauge_t value,
                                     cdtime_t time) {
  value_list_t vl = {.values = &(value_t){.gauge = value},
                     .values_len = 1,
                     .time = time,
                     .plugin = DPDK_EVENTS_PLUGIN,
                     .type = "gauge",
                     .meta = NULL};
  sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));
  plugin_dispatch_values(&vl);
}