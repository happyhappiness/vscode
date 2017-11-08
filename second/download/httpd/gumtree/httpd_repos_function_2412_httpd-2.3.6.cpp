unsigned long util_ldap_compare_node_hash(void *n)
{
    util_compare_node_t *node = n;
    return util_ald_hash_string(3, node->dn, node->attrib, node->value);
}