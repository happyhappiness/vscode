static int snmp_agent_unregister_oid_index(oid_t *oid, int index) {
  oid_t new_oid;
  memcpy(&new_oid, oid, sizeof(*oid));
  new_oid.oid[new_oid.oid_len++] = index;
  return unregister_mib(new_oid.oid, new_oid.oid_len);
}