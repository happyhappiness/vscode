void util_ldap_url_node_free(void *n)
{
    util_url_node_t *node = (util_url_node_t *)n;

    util_ald_free(node->url);
    util_ald_destroy_cache(node->search_cache);
    util_ald_destroy_cache(node->compare_cache);
    util_ald_destroy_cache(node->dn_compare_cache);
    util_ald_free(node);
}