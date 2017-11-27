static int snmp_agent_register_table_oids(void) {

  for (llentry_t *te = llist_head(g_agent->tables); te != NULL; te = te->next) {
    table_definition_t *td = te->value;

    if (td->size_oid.oid_len != 0) {
      td->size_oid.type =
          snmp_agent_get_asn_type(td->size_oid.oid, td->size_oid.oid_len);
      td->size_oid.oid_len++;
      int ret = snmp_agent_register_oid(&td->size_oid,
                                        snmp_agent_table_size_oid_handler);
      if (ret != 0)
        return ret;
    }

    for (llentry_t *de = llist_head(td->columns); de != NULL; de = de->next) {
      data_definition_t *dd = de->value;

      for (size_t i = 0; i < dd->oids_len; i++) {
        dd->oids[i].type =
            snmp_agent_get_asn_type(dd->oids[i].oid, dd->oids[i].oid_len);
      }
    }
  }

  return 0;
}