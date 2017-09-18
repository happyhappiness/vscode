    util_ald_free(cache, node->dn);
    util_ald_free(cache, node->attrib);
    util_ald_free(cache, node->value);
    util_ald_free(cache, node);
}

/* ------------------------------------------------------------------ */

unsigned long util_ldap_dn_compare_node_hash(void *n)
{
    return util_ald_hash_string(1, ((util_dn_compare_node_t *)n)->reqdn);
}
