static int snmp_agent_table_size_oid_handler(
    struct netsnmp_mib_handler_s *handler,
    struct netsnmp_handler_registration_s *reginfo,
    struct netsnmp_agent_request_info_s *reqinfo,
    struct netsnmp_request_info_s *requests) {

  if (reqinfo->mode != MODE_GET && reqinfo->mode != MODE_GETNEXT) {
    DEBUG(PLUGIN_NAME ": Not supported request mode (%d)", reqinfo->mode);
    return SNMP_ERR_NOERROR;
  }

  pthread_mutex_lock(&g_agent->lock);

  oid_t oid;
  memcpy(oid.oid, requests->requestvb->name,
         sizeof(oid.oid[0]) * requests->requestvb->name_length);
  oid.oid_len = requests->requestvb->name_length;

  DEBUG(PLUGIN_NAME ": Get request received for table size OID");

  for (llentry_t *te = llist_head(g_agent->tables); te != NULL; te = te->next) {
    table_definition_t *td = te->value;

    if (td->size_oid.oid_len &&
        (snmp_oid_ncompare(oid.oid, oid.oid_len, td->size_oid.oid,
                           td->size_oid.oid_len,
                           MIN(oid.oid_len, td->size_oid.oid_len)) == 0)) {
      DEBUG(PLUGIN_NAME ": Handle '%s' table size OID", td->name);

      long size = c_avl_size(td->index_instance);

      requests->requestvb->type = td->size_oid.type;
      snmp_set_var_typed_value(requests->requestvb, requests->requestvb->type,
                               (const u_char *)&size, sizeof(size));

      pthread_mutex_unlock(&g_agent->lock);

      return SNMP_ERR_NOERROR;
    }
  }

  pthread_mutex_unlock(&g_agent->lock);

  return SNMP_NOSUCHINSTANCE;
}