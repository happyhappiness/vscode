static int snmp_agent_unregister_oid_string(oid_t *oid, const char *key) {
  oid_t new_oid;

  memcpy(&new_oid, oid, sizeof(*oid));
  int ret = snmp_agent_generate_string2oid(&new_oid, key);
  if (ret != 0)
    return ret;

  return unregister_mib(new_oid.oid, new_oid.oid_len);
}