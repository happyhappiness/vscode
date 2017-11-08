int util_ldap_dn_compare_node_compare(void *a, void *b)
{
    util_dn_compare_node_t *na = a;
    util_dn_compare_node_t *nb = b;

    return (strcmp(na->reqdn, nb->reqdn) == 0);
}