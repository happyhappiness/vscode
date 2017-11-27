static u_char snmp_agent_get_asn_type(oid *oid, size_t oid_len) {
  struct tree *node = get_tree(oid, oid_len, g_agent->tp);

  return (node != NULL) ? mib_to_asn_type(node->type) : 0;
}