static ovs_callback_t *ovs_db_table_callback_get(ovs_db_t *pdb, yajl_val jid) {
  char *endptr = NULL;
  const char *suid = NULL;
  uint64_t uid;

  if (jid && YAJL_IS_STRING(jid)) {
    suid = YAJL_GET_STRING(jid);
    uid = (uint64_t)strtoul(suid, &endptr, 16);
    if (*endptr == '\0' && uid)
      return ovs_db_callback_get(pdb, uid);
  }

  return NULL;
}