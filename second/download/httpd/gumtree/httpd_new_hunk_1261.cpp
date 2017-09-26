 * Insert an item into the cache.
 * *** Does not catch duplicates!!! ***
 */
void *util_ald_cache_insert(util_ald_cache_t *cache, void *payload)
{
    unsigned long hashval;
    void *tmp_payload;
    util_cache_node_t *node;

    /* sanity check */
    if (cache == NULL || payload == NULL) {
        return NULL;
    }

    /* check if we are full - if so, try purge */
    if (cache->numentries >= cache->maxentries) {
        util_ald_cache_purge(cache);
        if (cache->numentries >= cache->maxentries) {
            /* if the purge was not effective, we leave now to avoid an overflow */
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
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
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
                     "LDAPSharedCacheSize is too small. Increase it or "
                     "reduce LDAPCacheEntries/LDAPOpCacheEntries!");
        if (cache->numentries < cache->fullmark) {
            /*
             * We have not even reached fullmark, trigger a complete purge.
             * This is still better than not being able to add new entries
             * at all.
             */
            cache->marktime = apr_time_now();
        }
        util_ald_cache_purge(cache);
        node = (util_cache_node_t *)util_ald_alloc(cache,
                                                   sizeof(util_cache_node_t));
        if (node == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                         "Could not allocate memory for LDAP cache entry");
            return NULL;
        }
    }

    /* Take a copy of the payload before proceeeding. */
    tmp_payload = (*cache->copy)(cache, payload);
    if (tmp_payload == NULL) {
        /*
         * XXX: The cache management should be rewritten to work
         * properly when LDAPSharedCacheSize is too small.
         */
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
                     "LDAPSharedCacheSize is too small. Increase it or "
                     "reduce LDAPCacheEntries/LDAPOpCacheEntries!");
        if (cache->numentries < cache->fullmark) {
            /*
             * We have not even reached fullmark, trigger a complete purge.
             * This is still better than not being able to add new entries
             * at all.
             */
            cache->marktime = apr_time_now();
        }
        util_ald_cache_purge(cache);
        tmp_payload = (*cache->copy)(cache, payload);
        if (tmp_payload == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                         "Could not allocate memory for LDAP cache value");
            util_ald_free(cache, node);
            return NULL;
        }
    }
    payload = tmp_payload;

    /* populate the entry */
    cache->inserts++;
    hashval = (*cache->hash)(payload) % cache->size;
    node->add_time = apr_time_now();
    node->payload = payload;
