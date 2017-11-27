static int snmp_agent_register_oid_index(oid_t *oid, int index,
                                         Netsnmp_Node_Handler *handler) {
  oid_t new_oid;
  memcpy(&new_oid, oid, sizeof(*oid));
  new_oid.oid[new_oid.oid_len++] = index;
  return snmp_agent_register_oid(&new_oid, handler);
}