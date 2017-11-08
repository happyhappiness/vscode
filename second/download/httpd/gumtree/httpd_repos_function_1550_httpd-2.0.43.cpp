void *util_ldap_url_node_copy(void *c)
{
    util_url_node_t *n = (util_url_node_t *)c;
    util_url_node_t *node = (util_url_node_t *)util_ald_alloc(sizeof(util_url_node_t));

    if (node) {
        if (!(node->url = util_ald_strdup(n->url))) {
            util_ald_free(node->url);
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