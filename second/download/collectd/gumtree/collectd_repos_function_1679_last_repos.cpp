static void snmp_agent_free_data(data_definition_t **dd) {

  if (dd == NULL || *dd == NULL)
    return;

  /* unregister scalar type OID */
  if ((*dd)->table == NULL) {
    for (size_t i = 0; i < (*dd)->oids_len; i++)
      unregister_mib((*dd)->oids[i].oid, (*dd)->oids[i].oid_len);
  }

  sfree((*dd)->name);
  sfree((*dd)->plugin);
  sfree((*dd)->plugin_instance);
  sfree((*dd)->type);
  sfree((*dd)->type_instance);
  sfree((*dd)->oids);

  sfree(*dd);

  return;
}