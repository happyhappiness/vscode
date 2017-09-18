    util_ald_destroy_cache(node->search_cache);
    util_ald_destroy_cache(node->compare_cache);
    util_ald_destroy_cache(node->dn_compare_cache);
    util_ald_free(cache, node);
}

/* ------------------------------------------------------------------ */

/* Cache functions for search nodes */
unsigned long util_ldap_search_node_hash(void *n)
{
    util_search_node_t *node = (util_search_node_t *)n;
