static void ovs_stats_submit_one(const char *dev, const char *type,
                                 const char *type_instance, derive_t value,
                                 meta_data_t *meta) {
  /* if counter is less than 0 - skip it*/
  if (value < 0)
    return;
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.derive = value};
  vl.values_len = 1;
  vl.meta = meta;

  sstrncpy(vl.plugin, plugin_name, sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, dev, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));

  if (type_instance != NULL)
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}