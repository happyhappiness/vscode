static int snmp_agent_config_table(oconfig_item_t *ci) {
  table_definition_t *td;
  int ret = 0;

  assert(ci != NULL);

  td = calloc(1, sizeof(*td));
  if (td == NULL) {
    ERROR(PLUGIN_NAME ": Failed to allocate memory for table definition");
    return -ENOMEM;
  }

  ret = cf_util_get_string(ci, &td->name);
  if (ret != 0) {
    sfree(td);
    return -1;
  }

  td->columns = llist_create();
  if (td->columns == NULL) {
    ERROR(PLUGIN_NAME ": Failed to allocate memory for columns list");
    snmp_agent_free_table(&td);
    return -ENOMEM;
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp("IndexOID", option->key) == 0)
      ret = snmp_agent_config_table_index_oid(td, option);
    else if (strcasecmp("SizeOID", option->key) == 0)
      ret = snmp_agent_config_table_size_oid(td, option);
    else if (strcasecmp("Data", option->key) == 0)
      ret = snmp_agent_config_table_data(td, option);
    else {
      WARNING(PLUGIN_NAME ": Option `%s' not allowed here", option->key);
      ret = -1;
    }

    if (ret != 0) {
      snmp_agent_free_table(&td);
      return -ENOMEM;
    }
  }

  td->instance_index =
      c_avl_create((int (*)(const void *, const void *))strcmp);
  if (td->instance_index == NULL) {
    snmp_agent_free_table(&td);
    return -ENOMEM;
  }

  td->index_instance =
      c_avl_create((int (*)(const void *, const void *))num_compare);
  if (td->index_instance == NULL) {
    snmp_agent_free_table(&td);
    return -ENOMEM;
  }

  llentry_t *entry = llentry_create(td->name, td);
  if (entry == NULL) {
    snmp_agent_free_table(&td);
    return -ENOMEM;
  }
  llist_append(g_agent->tables, entry);

  return 0;
}