static void ethstat_submit_value(const char *device, const char *type_instance,
                                 derive_t value) {
  static c_complain_t complain_no_map = C_COMPLAIN_INIT_STATIC;

  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;
  value_map_t *map = NULL;

  if (value_map != NULL)
    c_avl_get(value_map, type_instance, (void *)&map);

  /* If the "MappedOnly" option is specified, ignore unmapped values. */
  if (collect_mapped_only && (map == NULL)) {
    if (value_map == NULL)
      c_complain(
          LOG_WARNING, &complain_no_map,
          "ethstat plugin: The \"MappedOnly\" option has been set to true, "
          "but no mapping has been configured. All values will be ignored!");
    return;
  }

  values[0].derive = value;
  vl.values = values;
  vl.values_len = 1;

  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "ethstat", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, device, sizeof(vl.plugin_instance));
  if (map != NULL) {
    sstrncpy(vl.type, map->type, sizeof(vl.type));
    sstrncpy(vl.type_instance, map->type_instance, sizeof(vl.type_instance));
  } else {
    sstrncpy(vl.type, "derive", sizeof(vl.type));
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));
  }

  plugin_dispatch_values(&vl);
}