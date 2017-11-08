char *util_ald_cache_display_stats(request_rec *r, util_ald_cache_t *cache, char *name, char *id)
{
    unsigned long i;
    int totchainlen = 0;
    int nchains = 0;
    double chainlen;
    util_cache_node_t *n;
    char *buf, *buf2;
    apr_pool_t *p = r->pool;

    if (cache == NULL) {
        return "";
    }

    for (i=0; i < cache->size; ++i) {
        if (cache->nodes[i] != NULL) {
            nchains++;
            for (n = cache->nodes[i];
                 n != NULL && n != n->next;
                 n = n->next) {
                totchainlen++;
            }
        }
    }
    chainlen = nchains? (double)totchainlen / (double)nchains : 0;

    if (id) {
        buf2 = apr_psprintf(p,
                 "<a href=\"%s?%s\">%s</a>",
             r->uri,
             id,
             name);
    }
    else {
        buf2 = name;
    }

    buf = apr_psprintf(p,
             "<tr valign='top'>"
             "<td nowrap>%s</td>"
             "<td align='right' nowrap>%lu (%.0f%% full)</td>"
             "<td align='right'>%.1f</td>"
             "<td align='right'>%lu/%lu</td>"
             "<td align='right'>%.0f%%</td>"
             "<td align='right'>%lu/%lu</td>",
         buf2,
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

    buf = apr_psprintf(p, "%s<td align='right'>%.2gms</td>\n</tr>", buf, cache->avg_purgetime);

    return buf;
}