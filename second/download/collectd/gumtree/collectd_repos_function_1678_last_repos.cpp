static int snmp_agent_table_row_remove(table_definition_t *td,
                                       const char *instance) {
  int *index = NULL;
  char *ins = NULL;

  if (td->index_oid.oid_len) {
    if ((c_avl_get(td->instance_index, instance, (void **)&index) != 0) ||
        (c_avl_get(td->index_instance, index, (void **)&ins) != 0))
      return 0;
  } else {
    if (c_avl_get(td->instance_index, instance, (void **)&ins) != 0)
      return 0;
  }

  pthread_mutex_lock(&g_agent->agentx_lock);

  if (td->index_oid.oid_len)
    snmp_agent_unregister_oid_index(&td->index_oid, *index);

  for (llentry_t *de = llist_head(td->columns); de != NULL; de = de->next) {
    data_definition_t *dd = de->value;

    for (size_t i = 0; i < dd->oids_len; i++)
      if (td->index_oid.oid_len)
        snmp_agent_unregister_oid_index(&dd->oids[i], *index);
      else
        snmp_agent_unregister_oid_string(&dd->oids[i], ins);
  }

  pthread_mutex_unlock(&g_agent->agentx_lock);

  DEBUG(PLUGIN_NAME ": Removed row for '%s' table [%d, %s]", td->name,
        (index != NULL) ? *index : -1, ins);

  notification_t n = {
      .severity = NOTIF_WARNING, .time = cdtime(), .plugin = PLUGIN_NAME};
  sstrncpy(n.host, hostname_g, sizeof(n.host));
  sstrncpy(n.plugin_instance, ins, sizeof(n.plugin_instance));
  snprintf(n.message, sizeof(n.message),
           "Removed data row from table %s instance %s index %d", td->name, ins,
           (index != NULL) ? *index : -1);
  plugin_dispatch_notification(&n);

  if (td->index_oid.oid_len) {
    c_avl_remove(td->index_instance, index, NULL, (void **)&ins);
    c_avl_remove(td->instance_index, instance, NULL, (void **)&index);
    sfree(index);
    sfree(ins);
  } else {
    c_avl_remove(td->instance_index, instance, NULL, (void **)&ins);
    sfree(ins);
  }

  return 0;
}