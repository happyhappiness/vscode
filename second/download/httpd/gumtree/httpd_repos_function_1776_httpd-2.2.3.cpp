int util_ldap_url_node_compare(void *a, void *b)
{
    util_url_node_t *na = a;
    util_url_node_t *nb = b;

    return (strcmp(na->url, nb->url) == 0);
}