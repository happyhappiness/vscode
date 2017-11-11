void util_ldap_search_node_free(util_ald_cache_t *cache, void *n)
{
    int i = 0;
    util_search_node_t *node = n;
    int k = node->numvals;

    if (node->vals) {
        for (;k;k--,i++) {
            if (node->vals[i]) {
                util_ald_free(cache, node->vals[i]);
            }
        }
        util_ald_free(cache, node->vals);
    }
    util_ald_free(cache, node->username);
    util_ald_free(cache, node->dn);
    util_ald_free(cache, node->bindpw);
    util_ald_free(cache, node);
}