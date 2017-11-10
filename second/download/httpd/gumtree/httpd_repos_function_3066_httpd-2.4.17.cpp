int util_ldap_compare_node_compare(void *a, void *b)
{
    util_compare_node_t *na = a;
    util_compare_node_t *nb = b;

    return (strcmp(na->dn, nb->dn) == 0 &&
            strcmp(na->attrib, nb->attrib) == 0 &&
            strcmp(na->value, nb->value) == 0);
}