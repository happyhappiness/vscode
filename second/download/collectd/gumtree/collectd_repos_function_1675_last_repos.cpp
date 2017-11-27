static int snmp_agent_generate_string2oid(oid_t *oid, const char *key) {
  int key_len = strlen(key);

  oid->oid[oid->oid_len++] = key_len;
  for (int i = 0; i < key_len; i++) {
    oid->oid[oid->oid_len++] = key[i];
    if (oid->oid_len >= MAX_OID_LEN) {
      ERROR(PLUGIN_NAME ": Conversion key string %s to OID failed", key);
      return -EINVAL;
    }
  }

  return 0;
}