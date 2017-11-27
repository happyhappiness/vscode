static void submit_hp(const struct entry_info *info) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = NAN};
  vl.values_len = 1;

  sstrncpy(vl.plugin, g_plugin_name, sizeof(vl.plugin));
  if (info->node) {
    snprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%s-%zuKb",
             info->node, info->page_size_kb);
  } else {
    snprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%zuKb",
             info->page_size_kb);
  }

  /* ensure all metrics have the same timestamp */
  vl.time = cdtime();

  gauge_t free = info->free;
  gauge_t used = (info->nr + info->surplus) - info->free;

  if (g_values_pages) {
    sstrncpy(vl.type, "vmpage_number", sizeof(vl.type));
    plugin_dispatch_multivalue(&vl, /* store_percentage = */ 0, DS_TYPE_GAUGE,
                               "free", free, "used", used, NULL);
  }
  if (g_values_bytes) {
    gauge_t page_size = (gauge_t)(1024 * info->page_size_kb);
    sstrncpy(vl.type, "memory", sizeof(vl.type));
    plugin_dispatch_multivalue(&vl, /* store_percentage = */ 0, DS_TYPE_GAUGE,
                               "free", free * page_size, "used",
                               used * page_size, NULL);
  }
  if (g_values_percent) {
    sstrncpy(vl.type, "percent", sizeof(vl.type));
    plugin_dispatch_multivalue(&vl, /* store_percentage = */ 1, DS_TYPE_GAUGE,
                               "free", free, "used", used, NULL);
  }
}