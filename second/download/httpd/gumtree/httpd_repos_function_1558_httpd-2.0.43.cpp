void *util_ldap_compare_node_copy(void *c)
{
    util_compare_node_t *n = (util_compare_node_t *)c;
    util_compare_node_t *node = (util_compare_node_t *)util_ald_alloc(sizeof(util_compare_node_t));

    if (node) {
        if (!(node->dn = util_ald_strdup(n->dn)) ||
            !(node->attrib = util_ald_strdup(n->attrib)) ||
            !(node->value = util_ald_strdup(n->value))) {
            util_ldap_compare_node_free(node);
            return NULL;
        }
        node->lastcompare = n->lastcompare;
        node->result = n->result;
        return node;
    }
    else {
        return NULL;
    }
}