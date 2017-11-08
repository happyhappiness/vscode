unsigned long util_ldap_search_node_hash(void *n)
{
    util_search_node_t *node = n;
    return util_ald_hash_string(1, node->username);
}