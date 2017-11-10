int util_ldap_search_node_compare(void *a, void *b)
{
    util_search_node_t *na = a;
    util_search_node_t *nb = b;

    return (strcmp(na->username, nb->username) == 0);
}