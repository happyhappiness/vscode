void util_ldap_search_node_free(void *n)
{
    int i = 0;
    util_search_node_t *node = (util_search_node_t *)n;
    if (node->vals) {
        while (node->vals[i]) {
            util_ald_free(node->vals[i++]);
        }
        util_ald_free(node->vals);
    }
    util_ald_free(node->username);
    util_ald_free(node->dn);
    util_ald_free(node->bindpw);
    util_ald_free(node);
}