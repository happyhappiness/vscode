int util_ldap_url_node_compare(void *a, void *b)
{
    util_url_node_t *na = (util_url_node_t *)a;
    util_url_node_t *nb = (util_url_node_t *)b;

    return(strcmp(na->url, nb->url) == 0);
}