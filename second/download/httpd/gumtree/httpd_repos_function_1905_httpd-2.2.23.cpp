void util_ldap_compare_node_free(util_ald_cache_t *cache, void *n)
{
    util_compare_node_t *node = n;
    util_ald_free(cache, node->dn);
    util_ald_free(cache, node->attrib);
    util_ald_free(cache, node->value);
    util_ald_free(cache, node);
}