static int snmp_agent_config(oconfig_item_t *ci) {

  int ret = snmp_agent_preinit();

  if (ret != 0) {
    sfree(g_agent);
    return -EINVAL;
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("Data", child->key) == 0) {
      ret = snmp_agent_config_data(child);
    } else if (strcasecmp("Table", child->key) == 0) {
      ret = snmp_agent_config_table(child);
    } else {
      ERROR(PLUGIN_NAME ": Unknown configuration option `%s'", child->key);
      ret = (-EINVAL);
    }

    if (ret != 0) {
      ERROR(PLUGIN_NAME ": Failed to parse configuration");
      snmp_agent_free_config();
      snmp_shutdown(PLUGIN_NAME);
      sfree(g_agent);
      return -EINVAL;
    }
  }

  ret = snmp_agent_validate_data();
  if (ret != 0) {
    ERROR(PLUGIN_NAME ": Invalid configuration provided");
    snmp_agent_free_config();
    snmp_shutdown(PLUGIN_NAME);
    sfree(g_agent);
    return -EINVAL;
  }

  return 0;
}