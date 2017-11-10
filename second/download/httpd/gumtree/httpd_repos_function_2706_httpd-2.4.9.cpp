void *util_ldap_compare_node_copy(util_ald_cache_t *cache, void *c)
{
    util_compare_node_t *n = c;
    util_compare_node_t *node = util_ald_alloc(cache, sizeof *node);

    if (node) {
        if (!(node->dn = util_ald_strdup(cache, n->dn)) ||
            !(node->attrib = util_ald_strdup(cache, n->attrib)) ||
            !(node->value = util_ald_strdup(cache, n->value)) ||
            ((n->subgroupList) && !(node->subgroupList = util_ald_sgl_dup(cache, n->subgroupList)))) {
            util_ldap_compare_node_free(cache, node);
            return NULL;
        }
        node->lastcompare = n->lastcompare;
        node->result = n->result;
        node->sgl_processed = n->sgl_processed;
        return node;
    }
    else {
        return NULL;
    }
}