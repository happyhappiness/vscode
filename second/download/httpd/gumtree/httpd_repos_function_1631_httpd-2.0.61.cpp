int util_ldap_dn_compare_node_compare(void *a, void *b)
{
    return (strcmp(((util_dn_compare_node_t *)a)->reqdn,
		   ((util_dn_compare_node_t *)b)->reqdn) == 0);
}