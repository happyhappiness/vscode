    util_ald_free(cache, node->username);
    util_ald_free(cache, node->dn);
    util_ald_free(cache, node->bindpw);
    util_ald_free(cache, node);
}

/* ------------------------------------------------------------------ */

unsigned long util_ldap_compare_node_hash(void *n)
{
    util_compare_node_t *node = (util_compare_node_t *)n;
    return util_ald_hash_string(3, node->dn, node->attrib, node->value);
