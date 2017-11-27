static char *snmp_agent_get_oid_name(oid *oid, size_t oid_len) {
  struct tree *node = get_tree(oid, oid_len, g_agent->tp);

  return (node != NULL) ? node->label : NULL;
}