int util_ldap_search_node_compare(void *a, void *b)
{
    return(strcmp(((util_search_node_t *)a)->username,
		  ((util_search_node_t *)b)->username) == 0);
}