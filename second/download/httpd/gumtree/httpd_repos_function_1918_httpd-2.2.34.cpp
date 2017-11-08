void *util_ldap_url_node_copy(util_ald_cache_t *cache, void *c)
{
    util_url_node_t *n = c;
    util_url_node_t *node = util_ald_alloc(cache, sizeof *node);

    if (node) {
        if (!(node->url = util_ald_strdup(cache, n->url))) {
            util_ald_free(cache, node);
            return NULL;
        }
        node->search_cache = n->search_cache;
        node->compare_cache = n->compare_cache;
        node->dn_compare_cache = n->dn_compare_cache;
        return node;
    }
    else {
        return NULL;
    }
}