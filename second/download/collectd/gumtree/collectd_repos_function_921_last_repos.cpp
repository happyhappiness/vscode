static void submit(const char *plugin_instance, /* {{{ */
                   const char *pdns_type, const char *value_str) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t value;

  const char *type = NULL;
  const char *type_instance = NULL;
  const data_set_t *ds;

  int i;

  for (i = 0; i < lookup_table_length; i++)
    if (strcmp(lookup_table[i].name, pdns_type) == 0)
      break;

  if (i >= lookup_table_length) {
    INFO("powerdns plugin: submit: Not found in lookup table: %s = %s;",
         pdns_type, value_str);
    return;
  }

  if (lookup_table[i].type == NULL)
    return;

  type = lookup_table[i].type;
  type_instance = lookup_table[i].type_instance;

  ds = plugin_get_ds(type);
  if (ds == NULL) {
    ERROR("powerdns plugin: The lookup table returned type `%s', "
          "but I cannot find it via `plugin_get_ds'.",
          type);
    return;
  }

  if (ds->ds_num != 1) {
    ERROR("powerdns plugin: type `%s' has %zu data sources, "
          "but I can only handle one.",
          type, ds->ds_num);
    return;
  }

  if (0 != parse_value(value_str, &value, ds->ds[0].type)) {
    ERROR("powerdns plugin: Cannot convert `%s' "
          "to a number.",
          value_str);
    return;
  }

  vl.values = &value;
  vl.values_len = 1;
  sstrncpy(vl.plugin, "powerdns", sizeof(vl.plugin));
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_instance != NULL)
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));
  sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));

  plugin_dispatch_values(&vl);
}