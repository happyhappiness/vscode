char *util_ald_cache_display(apr_pool_t *pool)
{
    unsigned long i;
    char *buf, *t1, *t2, *t3;

    if (!util_ldap_cache) {
        return "<tr valign='top'><td nowrap colspan=7>Cache has not been enabled/initialised.</td></tr>";
    }

    buf = util_ald_cache_display_stats(pool, util_ldap_cache, "LDAP URL Cache");

    for (i=0; i < util_ldap_cache->size; ++i) {
        util_cache_node_t *p;
        for (p = util_ldap_cache->nodes[i]; p != NULL; p = p->next) {
            util_url_node_t *n;

            n = (util_url_node_t *)p->payload;

            t1 = apr_psprintf(pool, "%s (Searches)", n->url);
            t2 = apr_psprintf(pool, "%s (Compares)", n->url);
            t3 = apr_psprintf(pool, "%s (DNCompares)", n->url);

            buf = apr_psprintf(pool, "%s\n\n"
                                     "%s\n\n"
                                     "%s\n\n"
                                     "%s\n\n",
                                     buf,
                                     util_ald_cache_display_stats(pool, n->search_cache, t1),
                                     util_ald_cache_display_stats(pool, n->compare_cache, t2),
                                     util_ald_cache_display_stats(pool, n->dn_compare_cache, t3)
                              );
        }
    }
    return buf;
}