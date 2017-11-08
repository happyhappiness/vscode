void util_ldap_dn_compare_node_free(void *n)
{
    util_dn_compare_node_t *node = (util_dn_compare_node_t *)n;
    util_ald_free(node->reqdn);
    util_ald_free(node->dn);
    util_ald_free(node);
}