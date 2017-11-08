void util_ldap_compare_node_free(void *n)
{
    util_compare_node_t *node = (util_compare_node_t *)n;
    util_ald_free(node->dn);
    util_ald_free(node->attrib);
    util_ald_free(node->value);
    util_ald_free(node);
}