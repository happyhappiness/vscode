static int
snmp_agent_table_oid_handler(struct netsnmp_mib_handler_s *handler,
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
  DEBUG(PLUGIN_NAME ": Get request received for table OID '%s'", oid_str);
#endif

  for (llentry_t *te = llist_head(g_agent->tables); te != NULL; te = te->next) {
    table_definition_t *td = te->value;

    for (llentry_t *de = llist_head(td->columns); de != NULL; de = de->next) {
      data_definition_t *dd = de->value;

      for (size_t i = 0; i < dd->oids_len; i++) {
        int ret = snmp_oid_ncompare(oid.oid, oid.oid_len, dd->oids[i].oid,
                                    dd->oids[i].oid_len,
                                    MIN(oid.oid_len, dd->oids[i].oid_len));
        if (ret != 0)
          continue;

        char *instance;

        if (!td->index_oid.oid_len) {
          char key[MAX_OID_LEN];

          memset(key, 0, sizeof(key));
          snmp_agent_generate_oid2string(
              &oid, MIN(oid.oid_len, dd->oids[i].oid_len), key);

          ret = c_avl_get(td->instance_index, key, (void **)&instance);
          if (ret != 0) {
            DEBUG(PLUGIN_NAME ": Nonexisting index string '%s' requested", key);
            pthread_mutex_unlock(&g_agent->lock);
            return SNMP_NOSUCHINSTANCE;
          }
        } else {
          int index = oid.oid[oid.oid_len - 1];

          ret = c_avl_get(td->index_instance, &index, (void **)&instance);
          if (ret != 0) {
            DEBUG(PLUGIN_NAME ": Nonexisting index '%d' requested", index);
            pthread_mutex_unlock(&g_agent->lock);
            return SNMP_NOSUCHINSTANCE;
          }
        }

        if (dd->is_instance) {
          requests->requestvb->type = ASN_OCTET_STR;
          snmp_set_var_typed_value(
              requests->requestvb, requests->requestvb->type,
              (const u_char *)instance, strlen((instance)));

          pthread_mutex_unlock(&g_agent->lock);

          return SNMP_ERR_NOERROR;
        }

        ret = snmp_agent_form_reply(requests, dd, instance, i);

        pthread_mutex_unlock(&g_agent->lock);

        return ret;
      }
    }
  }

  pthread_mutex_unlock(&g_agent->lock);

  return SNMP_NOSUCHINSTANCE;
}