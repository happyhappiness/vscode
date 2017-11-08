unsigned long util_ldap_dn_compare_node_hash(void *n)
{
    util_dn_compare_node_t *node = n;
    return util_ald_hash_string(1, node->reqdn);
}