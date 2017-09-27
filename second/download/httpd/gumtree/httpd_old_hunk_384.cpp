    }
    (*cache->free)(cache, p->payload);
    util_ald_free(cache, p);
    cache->numentries--;
}

char *util_ald_cache_display_stats(apr_pool_t *p, util_ald_cache_t *cache, char *name)
{
    unsigned long i;
    int totchainlen = 0;
    int nchains = 0;
    double chainlen;
    util_cache_node_t *n;
    char *buf;

    if (cache == NULL) {
        return "";
    }

    for (i=0; i < cache->size; ++i) {
        if (cache->nodes[i] != NULL) {
            nchains++;
            for (n = cache->nodes[i]; n != NULL; n = n->next)
	        totchainlen++;
        }
    }
    chainlen = nchains? (double)totchainlen / (double)nchains : 0;

    buf = apr_psprintf(p, 
             "<tr valign='top'>"
             "<td nowrap>%s</td>"
             "<td align='right' nowrap>%lu (%.0f%% full)</td>"
             "<td align='right'>%.1f</td>"
	     "<td align='right'>%lu/%lu</td>"
	     "<td align='right'>%.0f%%</td>"
             "<td align='right'>%lu/%lu</td>",
             name,
	     cache->numentries, 
	     (double)cache->numentries / (double)cache->maxentries * 100.0,
             chainlen,
	     cache->hits, 	     
	     cache->fetches,
	     (cache->fetches > 0 ? (double)(cache->hits) / (double)(cache->fetches) * 100.0 : 100.0),
	     cache->inserts,
	     cache->removes);

    if (cache->numpurges) {
        char str_ctime[APR_CTIME_LEN];

        apr_ctime(str_ctime, cache->last_purge);
        buf = apr_psprintf(p,
                           "%s"
	                   "<td align='right'>%lu</td>\n"
                           "<td align='right' nowrap>%s</td>\n", 
                           buf,
	                   cache->numpurges,
	                   str_ctime);
    }
    else {
        buf = apr_psprintf(p, 
                           "%s<td colspan='2' align='center'>(none)</td>\n",
                           buf);
    }

    buf = apr_psprintf(p, "%s<td align='right'>%.2g</td>\n</tr>", buf, cache->avg_purgetime);

    return buf;
}

char *util_ald_cache_display(apr_pool_t *pool, util_ldap_state_t *st)
{
    unsigned long i;
    char *buf, *t1, *t2, *t3;

    util_ald_cache_t *util_ldap_cache = st->util_ldap_cache;


    if (!util_ldap_cache) {
        return "<tr valign='top'><td nowrap colspan=7>Cache has not been enabled/initialised.</td></tr>";
    }

    buf = util_ald_cache_display_stats(pool, st->util_ldap_cache, "LDAP URL Cache");

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

#endif /* APU_HAS_LDAP */
