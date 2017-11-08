void util_ldap_dn_compare_node_free(util_ald_cache_t *cache, void *n)
{
    util_dn_compare_node_t *node = (util_dn_compare_node_t *)n;
    util_ald_free(cache, node->reqdn);
    util_ald_free(cache, node->dn);
    util_ald_free(cache, node);
}