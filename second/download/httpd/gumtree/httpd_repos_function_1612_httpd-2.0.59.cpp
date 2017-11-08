unsigned long util_ldap_url_node_hash(void *n)
{
    util_url_node_t *node = (util_url_node_t *)n;
    return util_ald_hash_string(1, node->url);
}