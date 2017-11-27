static int snmp_agent_oid_to_string(char *buf, size_t buf_size,
                                    oid_t const *o) {
  char oid_str[MAX_OID_LEN][16];
  char *oid_str_ptr[MAX_OID_LEN];

  for (size_t i = 0; i < o->oid_len; i++) {
    snprintf(oid_str[i], sizeof(oid_str[i]), "%lu", (unsigned long)o->oid[i]);
    oid_str_ptr[i] = oid_str[i];
  }

  return strjoin(buf, buf_size, oid_str_ptr, o->oid_len, ".");
}