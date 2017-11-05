unsigned long util_ldap_url_node_hash(void *n)
{
    util_url_node_t *node = n;
    return util_ald_hash_string(1, node->url);
}