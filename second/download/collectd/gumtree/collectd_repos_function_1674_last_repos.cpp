static void snmp_agent_generate_oid2string(oid_t *oid, size_t offset,
                                           char *key) {
  int key_len = oid->oid[offset];
  int i;

  for (i = 0; i < key_len && offset < oid->oid_len; i++)
    key[i] = oid->oid[++offset];

  key[i] = '\0';
}