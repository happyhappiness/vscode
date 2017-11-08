int util_ldap_compare_node_compare(void *a, void *b)
{
    util_compare_node_t *na = (util_compare_node_t *)a;
    util_compare_node_t *nb = (util_compare_node_t *)b;
    return (strcmp(na->dn, nb->dn) == 0 &&
	    strcmp(na->attrib, nb->attrib) == 0 &&
	    strcmp(na->value, nb->value) == 0);
}