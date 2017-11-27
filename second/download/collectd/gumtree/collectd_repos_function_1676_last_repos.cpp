static int snmp_agent_register_oid_string(oid_t *oid, const char *key,
                                          Netsnmp_Node_Handler *handler) {
  oid_t new_oid;

  memcpy(&new_oid, oid, sizeof(*oid));
  int ret = snmp_agent_generate_string2oid(&new_oid, key);
  if (ret != 0)
    return ret;

  return snmp_agent_register_oid(&new_oid, handler);
}