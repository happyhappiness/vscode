static void load_submit(const char *plugin_instance, gauge_t snum, gauge_t mnum,
                        gauge_t lnum) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.gauge = snum}, {.gauge = mnum}, {.gauge = lnum},
  };

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "vserver", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "load", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}