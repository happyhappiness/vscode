static void submit_in_progress(char const *disk_name, gauge_t in_progress) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = in_progress};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "disk", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, disk_name, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "pending_operations", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}