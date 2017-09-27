
    /* check if we are full - if so, try purge */
    if (cache->numentries >= cache->maxentries) {
        util_ald_cache_purge(cache);
        if (cache->numentries >= cache->maxentries) {
            /* if the purge was not effective, we leave now to avoid an overflow */
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(01323)
                         "Purge of LDAP cache failed");
            return NULL;
        }
    }

    node = (util_cache_node_t *)util_ald_alloc(cache,
                                               sizeof(util_cache_node_t));
    if (node == NULL) {
        /*
         * XXX: The cache management should be rewritten to work
         * properly when LDAPSharedCacheSize is too small.
         */
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(01324)
                     "LDAPSharedCacheSize is too small. Increase it or "
                     "reduce LDAPCacheEntries/LDAPOpCacheEntries!");
        if (cache->numentries < cache->fullmark) {
            /*
             * We have not even reached fullmark, trigger a complete purge.
             * This is still better than not being able to add new entries
