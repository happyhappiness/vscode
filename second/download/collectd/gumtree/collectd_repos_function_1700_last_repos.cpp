static int snmp_agent_update_index(table_definition_t *td,
                                   const char *instance) {

  if (c_avl_get(td->instance_index, instance, NULL) == 0)
    return 0;

  int ret;
  int *index = NULL;
  char *ins;

  ins = strdup(instance);
  if (ins == NULL)
    return -ENOMEM;

  /* need to generate index for the table */
  if (td->index_oid.oid_len) {
    index = calloc(1, sizeof(*index));
    if (index == NULL) {
      sfree(ins);
      return -ENOMEM;
    }

    *index = c_avl_size(td->instance_index) + 1;

    ret = c_avl_insert(td->instance_index, ins, index);
    if (ret != 0) {
      sfree(ins);
      sfree(index);
      return ret;
    }

    ret = c_avl_insert(td->index_instance, index, ins);
    if (ret < 0) {
      DEBUG(PLUGIN_NAME ": Failed to update index_instance for '%s' table",
            td->name);
      c_avl_remove(td->instance_index, ins, NULL, (void **)&index);
      sfree(ins);
      sfree(index);
      return ret;
    }

    ret = snmp_agent_register_oid_index(&td->index_oid, *index,
                                        snmp_agent_table_index_oid_handler);
    if (ret != 0)
      return ret;
  } else {
    /* instance as a key is required for any table */
    ret = c_avl_insert(td->instance_index, ins, ins);
    if (ret != 0) {
      sfree(ins);
      return ret;
    }
  }

  /* register new oids for all columns */
  for (llentry_t *de = llist_head(td->columns); de != NULL; de = de->next) {
    data_definition_t *dd = de->value;

    for (size_t i = 0; i < dd->oids_len; i++) {
      if (td->index_oid.oid_len) {
        ret = snmp_agent_register_oid_index(&dd->oids[i], *index,
                                            snmp_agent_table_oid_handler);
      } else {
        ret = snmp_agent_register_oid_string(&dd->oids[i], ins,
                                             snmp_agent_table_oid_handler);
      }

      if (ret != 0)
        return ret;
    }
  }

  DEBUG(PLUGIN_NAME ": Updated index for '%s' table [%d, %s]", td->name,
        (index != NULL) ? *index : -1, ins);

  notification_t n = {
      .severity = NOTIF_OKAY, .time = cdtime(), .plugin = PLUGIN_NAME};
  sstrncpy(n.host, hostname_g, sizeof(n.host));
  sstrncpy(n.plugin_instance, ins, sizeof(n.plugin_instance));
  snprintf(n.message, sizeof(n.message),
           "Data row added to table %s instance %s index %d", td->name, ins,
           (index != NULL) ? *index : -1);
  plugin_dispatch_notification(&n);

  return 0;
}