static int
snmp_agent_scalar_oid_handler(struct netsnmp_mib_handler_s *handler,
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

#if COLLECT_DEBUG
  char oid_str[DATA_MAX_NAME_LEN];
  snmp_agent_oid_to_string(oid_str, sizeof(oid_str), &oid);
  DEBUG(PLUGIN_NAME ": Get request received for scalar OID '%s'", oid_str);
#endif

  for (llentry_t *de = llist_head(g_agent->scalars); de != NULL;
       de = de->next) {
    data_definition_t *dd = de->value;

    for (size_t i = 0; i < dd->oids_len; i++) {

      int ret = snmp_oid_compare(oid.oid, oid.oid_len, dd->oids[i].oid,
                                 dd->oids[i].oid_len);
      if (ret != 0)
        continue;

      ret = snmp_agent_form_reply(requests, dd, NULL, i);

      pthread_mutex_unlock(&g_agent->lock);

      return ret;
    }
  }

  pthread_mutex_unlock(&g_agent->lock);

  return SNMP_NOSUCHINSTANCE;
}