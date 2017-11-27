static int snmp_agent_config_data(oconfig_item_t *ci) {
  data_definition_t *dd;
  int ret = 0;

  assert(ci != NULL);

  dd = calloc(1, sizeof(*dd));
  if (dd == NULL) {
    ERROR(PLUGIN_NAME ": Failed to allocate memory for data definition");
    return -ENOMEM;
  }

  ret = cf_util_get_string(ci, &dd->name);
  if (ret != 0) {
    free(dd);
    return -1;
  }

  dd->scale = 1.0;
  dd->shift = 0.0;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp("Instance", option->key) == 0)
      ret = cf_util_get_boolean(option, &dd->is_instance);
    else if (strcasecmp("Plugin", option->key) == 0)
      ret = cf_util_get_string(option, &dd->plugin);
    else if (strcasecmp("PluginInstance", option->key) == 0)
      ret = cf_util_get_string(option, &dd->plugin_instance);
    else if (strcasecmp("Type", option->key) == 0)
      ret = cf_util_get_string(option, &dd->type);
    else if (strcasecmp("TypeInstance", option->key) == 0)
      ret = cf_util_get_string(option, &dd->type_instance);
    else if (strcasecmp("Shift", option->key) == 0)
      ret = cf_util_get_double(option, &dd->shift);
    else if (strcasecmp("Scale", option->key) == 0)
      ret = cf_util_get_double(option, &dd->scale);
    else if (strcasecmp("OIDs", option->key) == 0)
      ret = snmp_agent_config_data_oids(dd, option);
    else {
      WARNING(PLUGIN_NAME ": Option `%s' not allowed here", option->key);
      ret = -1;
    }

    if (ret != 0) {
      snmp_agent_free_data(&dd);
      return -1;
    }
  }

  llentry_t *entry = llentry_create(dd->name, dd);
  if (entry == NULL) {
    snmp_agent_free_data(&dd);
    return -ENOMEM;
  }

  llist_append(g_agent->scalars, entry);

  return 0;
}