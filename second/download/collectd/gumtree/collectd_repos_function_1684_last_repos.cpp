static int snmp_agent_table_index_oid_handler(
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

  for (llentry_t *te = llist_head(g_agent->tables); te != NULL; te = te->next) {
    table_definition_t *td = te->value;

    if (td->index_oid.oid_len &&
        (snmp_oid_ncompare(oid.oid, oid.oid_len, td->index_oid.oid,
                           td->index_oid.oid_len,
                           MIN(oid.oid_len, td->index_oid.oid_len)) == 0)) {

      DEBUG(PLUGIN_NAME ": Handle '%s' table index OID", td->name);

      int index = oid.oid[oid.oid_len - 1];

      int ret = c_avl_get(td->index_instance, &index, &(void *){NULL});
      if (ret != 0) {
        /* nonexisting index requested */
        pthread_mutex_unlock(&g_agent->lock);
        return SNMP_NOSUCHINSTANCE;
      }

      requests->requestvb->type = ASN_INTEGER;
      snmp_set_var_typed_value(requests->requestvb, requests->requestvb->type,
                               (const u_char *)&index, sizeof(index));

      pthread_mutex_unlock(&g_agent->lock);

      return SNMP_ERR_NOERROR;
    }
  }

  pthread_mutex_unlock(&g_agent->lock);

  return SNMP_NOSUCHINSTANCE;
}