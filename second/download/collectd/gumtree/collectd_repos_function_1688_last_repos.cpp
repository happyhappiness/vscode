static int snmp_agent_register_scalar_oids(void) {

  for (llentry_t *e = llist_head(g_agent->scalars); e != NULL; e = e->next) {
    data_definition_t *dd = e->value;

    for (size_t i = 0; i < dd->oids_len; i++) {

      dd->oids[i].type =
          snmp_agent_get_asn_type(dd->oids[i].oid, dd->oids[i].oid_len);

      int ret =
          snmp_agent_register_oid(&dd->oids[i], snmp_agent_scalar_oid_handler);
      if (ret != 0)
        return ret;
    }
  }

  return 0;
}